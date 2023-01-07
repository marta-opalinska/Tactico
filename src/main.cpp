/** Copyright 2022 <Marta Opalinska> **/

// Tactico framework imports
#include <Tactico.h>

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#define ARDUINNO_NANO_RED 22
#define ARDUINNO_NANO_BLUE 24
#define ARDUINNO_NANO_GREEN 23

#include <Arduino.h>
// #undef min
// #undef max

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  /*
  Drivers, Actuators, Patterns and Action setup
  */

  // ----------------- GPIO DRIVER SETUP
  // pin that is connected to the actuator and supports Pulse Width-Modulation
  int driverPinGPIO = 22;
  // GPIO Driver - uses PMW patterns
  std::shared_ptr<ActuatorDriverGPIO> driver_GPIO =
      std::make_shared<ActuatorDriverGPIO>(driverPinGPIO);

  // ----------------- DRV2605LEVM DRIVER SETUP
  // DRV2605L evaluation board contains multiple DRV2605L drivers.
  // Therefore the driver ID need to be specified.
  int driverID_1 = 0;
  // the pin connected to DRV2605LEVM-MD board that triggers the haptic effects
  int driverGoPin = 12;

  // DRV2605L Driver - communicated through I2C
  //                    uses DRV2605L effect library pattern
  std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_DRV2605L_1 =
      std::make_shared<ActuatorDriverDRV2605LEVM>(driverID_1, driverGoPin);

  // Another driver from DRV2605LEVM board - this time with driver ID 1
  int driverID_2 = 1;

  std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_DRV2605L_2 =
      std::make_shared<ActuatorDriverDRV2605LEVM>(driverID_2, driverGoPin);

  // ----------------- ERM ACTUATOR SETUP

  // ----------------- ERM WITH GPIO DRIVER
  // the standard DC voltage for the actuator
  float ratedVoltage_ERM_1 = 2.0;
  // the maximum allowable DC voltage
  float overdriveVoltage_ERM_1 = 2.5;
  // optional - custom name will be prited alongside logs refering to the
  // actuator
  std::string customName_ERM_1 = "myERM_1";

  std::shared_ptr<ActuatorERM> actuator_ERM_1 =
      std::make_shared<ActuatorERM>(driver_GPIO, ratedVoltage_ERM_1,
                                    overdriveVoltage_ERM_1, customName_ERM_1);

  // It is recommended to test the connection with the actuator before
  // developing the code further - the actuator should vibrate
  actuator_ERM_1->test();

  // ----------------- ERM WITH DRV2605LEVM DRIVER
  float ratedVoltage_ERM_2 = 2.0;
  float overdriveVoltage_ERM_2 = 2.5;

  std::string customName_ERM_2 = "myERM_2";

  std::shared_ptr<ActuatorERM> actuator_ERM_2 =
      std::make_shared<ActuatorERM>(driver_DRV2605L_1, ratedVoltage_ERM_2,
                                    overdriveVoltage_ERM_2, customName_ERM_2);

  // It is recommended to test the connection with the actuator before
  // developing the code further - the actuator should vibrate
  actuator_ERM_2->test();

  // ----------------- LRA ACTUATOR SETUP

  // the standard DC voltage for the actuator
  float ratedVoltage_LRA = 2.0;
  // the maximum allowable DC voltage
  float overdriveVoltage_LRA = 2.5;
  // LRA actuator resonant frequency (can be found in the datasheet)
  int resonantFrequency_LRA = 170;
  // optional - custom name will be prited alongside logs refering to the
  // actuator
  std::string customName_LRA = "myLRA_1";

  std::shared_ptr<ActuatorLRA> actuator_LRA = std::make_shared<ActuatorLRA>(
      driver_DRV2605L_2, ratedVoltage_LRA, overdriveVoltage_LRA,
      resonantFrequency_LRA, customName_LRA);

  // It is recommended to test the connection with the actuator before
  // developing the code further - the actuator should vibrate
  actuator_LRA->test();

  // ----------------- PWM PATTERN SETUP

  /*
      Custom Pulse Width Mudulation that specifies
      duration in miliseconds (in this example 100ms and 50ms)
      and status (1 = true = ON or 0 = false = OFF)
  */
  std::vector<ModulationPWM> modulationPWM = {
      {100, true}, {50, false}, {100, true},
      {50, false}, {100, true}, {50, false},
  };

  std::shared_ptr<PatternPWM> pattern_PWM_1 =
      std::make_shared<PatternPWM>(modulationPWM);

  // ----------------- DRV2605L PATTERN SETUP

  /*
  All in-build effect available for the DRV2605L can be found in
  DRV2605L_EFFECTS.h file
  */
  std::shared_ptr<PatternDRV2605L> pattern_DRV2605L_CLICK =
      std::make_shared<PatternDRV2605L>(STRONG_CLICK_100);

  std::shared_ptr<PatternDRV2605L> pattern_DRV2605L_BUZZ =
      std::make_shared<PatternDRV2605L>(STRONG_BUZZ_100);

  // ----------------- ACTION STEPS SETUP

  // ----------------- WAIT STEPS

  // duration of the wait in miliseconds - 200ms
  int waitTime_200 = 200;

  std::shared_ptr<WaitStep> s_wait_200 =
      std::make_shared<WaitStep>(waitTime_200);

  // duration of the wait in miliseconds - 400ms
  int waitTime_400 = 200;

  std::shared_ptr<WaitStep> s_wait_400 =
      std::make_shared<WaitStep>(waitTime_400);

  // ----------------- ACTUATOR STEPS

  // step that combines actuator_ERM_1 with pattern pattern_PWM_1 -
  // This step is not parallel. Step's constructor field 'isParallel' is FALSE
  // by default. No need to specify it.
  std::shared_ptr<ActuatorStep> s_ERM_1_PWM_1 =
      std::make_shared<ActuatorStep>(actuator_ERM_1, pattern_PWM_1);

  bool isParallel_yes = true;
  // step that combines actuator_ERM_2 with pattern_DRV2605L_CLICK - this step
  // is run in parallel
  std::shared_ptr<ActuatorStep> s_ERM_2_DRV2605L_CLICK_PARALLEL =
      std::make_shared<ActuatorStep>(actuator_ERM_2, pattern_DRV2605L_CLICK,
                                     isParallel_yes);

  std::shared_ptr<ActuatorStep> s_LRA_DRV2605L_CLICK_PARALLEL =
      std::make_shared<ActuatorStep>(actuator_LRA, pattern_DRV2605L_CLICK,
                                     isParallel_yes);

  // step that combines s_ERM_2_DRV2605L_BUZZ with pattern_DRV2605L_CLICK
  // This step is not parallel.
  std::shared_ptr<ActuatorStep> s_ERM_2_DRV2605L_BUZZ =
      std::make_shared<ActuatorStep>(actuator_ERM_2, pattern_DRV2605L_BUZZ);

  // ----------------- ACTIONS SETUP

  std::shared_ptr<Action> a_forward = std::make_shared<Action>();

  a_forward->setSteps({s_ERM_1_PWM_1, s_wait_200, s_ERM_2_DRV2605L_BUZZ});

  std::shared_ptr<Action> a_forward_and_right = std::make_shared<Action>();

  a_forward_and_right->addStep(s_ERM_1_PWM_1);
  a_forward_and_right->addStep(s_wait_400);
  a_forward_and_right->addStep(s_LRA_DRV2605L_CLICK_PARALLEL);
  a_forward_and_right->addStep(s_ERM_2_DRV2605L_CLICK_PARALLEL);

  // ----------------- HAPTIC DEVICE SETUP

  HapticDevice haptic_band({actuator_ERM_1, actuator_ERM_2, actuator_LRA});
  haptic_band.addAction(a_forward, "go-forward");

  haptic_band.addAction(a_forward_and_right, "go-forward-and-right");

  haptic_band.testActuators();

  while (1) {
    haptic_band.configureAction("go-forward");
    delay(2000);
    haptic_band.playAction("go-forward");
    haptic_band.resetActuatorsPreRunConfiguration();
    delay(1000);
    haptic_band.configureAndPlayAction("go-forward-and-right");
  }
  //   std::shared_ptr<ActuatorStep> s_ac3 =
  //       std::make_shared<ActuatorStep>(ac_3, p_2, true);
  //   std::shared_ptr<ActuatorStep> s_ac4 =
  //       std::make_shared<ActuatorStep>(ac_4, p_2, true);
  //   std::shared_ptr<ActuatorStep> s_ac5 =
  //       std::make_shared<ActuatorStep>(ac_5, p_2, true);

  //   std::shared_ptr<ActuatorStep> s_PWM =
  //       std::make_shared<ActuatorStep>(ac_1, p_1);

  //   std::shared_ptr<ActuatorERM> ac_1 =
  //       std::make_shared<ActuatorERM>(driver_1, 2, 3);
  //   // std::shared_ptr<ActuatorERM> ac_2 =
  //   // std::make_shared<ActuatorERM>(driver_2);
  //   HapticDevice right_hand(ac_1);

  //   std::shared_ptr<Action> a_left = std::make_shared<Action>();
  //   std::shared_ptr<Action> a_right = std::make_shared<Action>();
  //   std::vector<ModulationPWM> mod_1 = {
  //       {100, true}, {50, false}, {40, true}, {30, false}, {20, true}};
  //   // std::vector<ModulationPWM> mod_2 = {{200, false}};
  //   std::shared_ptr<PatternPWM> p_1 =
  //   std::make_shared<PatternPWM>(mod_1);

  //   ac_1->play(p_1);

  //   int driverGoPin2 = 12;
  //   // driverGoPin2 = PIN_LED1;
  //   std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_2 =
  //       std::make_shared<ActuatorDriverDRV2605LEVM>(0, driverGoPin2);
  //   std::shared_ptr<ActuatorLRA> ac_2 =
  //       // std::make_shared<ActuatorLRA>(driver_2, 2.5, 2.7, 170,
  //       "myLRA"); std::make_shared<ActuatorLRA>(driver_2, 2, 2.5, 170,
  //       "myLRA");

  //   std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_3 =
  //       std::make_shared<ActuatorDriverDRV2605LEVM>(1, driverGoPin2);
  //   std::shared_ptr<ActuatorERM> ac_3 =
  //       std::make_shared<ActuatorERM>(driver_3, 2, 2.5, "myERM");

  //   std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_4 =
  //       std::make_shared<ActuatorDriverDRV2605LEVM>(2, driverGoPin2);
  //   std::shared_ptr<ActuatorLRA> ac_4 =
  //       std::make_shared<ActuatorLRA>(driver_4, 2.0, 2.5, 170,
  //       "myLRA_2");

  //   std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_5 =
  //       std::make_shared<ActuatorDriverDRV2605LEVM>(3, driverGoPin2);
  //   std::shared_ptr<ActuatorERM> ac_5 =
  //       std::make_shared<ActuatorERM>(driver_5, 2, 2.5, "myERM_2");

  //   /*
  //   All in-build effect available for the DRV2605L can be found in
  //   DRV2605L_EFFECTS.h file
  //   */
  //   std::shared_ptr<PatternDRV2605L> p_2 =
  //       std::make_shared<PatternDRV2605L>(STRONG_CLICK_30);

  //   HapticDevice test_hand({ac_1, ac_2, ac_3, ac_4, ac_5});

  //   test_hand.testActuators();

  //   setPinStatusTactico(driverPin1, HIGH);

  //   std::shared_ptr<ActuatorStep> s_ac2 =
  //       std::make_shared<ActuatorStep>(ac_2, p_2, true);
  //   std::shared_ptr<ActuatorStep> s_ac3 =
  //       std::make_shared<ActuatorStep>(ac_3, p_2, true);
  //   std::shared_ptr<ActuatorStep> s_ac4 =
  //       std::make_shared<ActuatorStep>(ac_4, p_2, true);
  //   std::shared_ptr<ActuatorStep> s_ac5 =
  //       std::make_shared<ActuatorStep>(ac_5, p_2, true);

  //   std::shared_ptr<ActuatorStep> s_PWM =
  //       std::make_shared<ActuatorStep>(ac_1, p_1);

  //   std::shared_ptr<WaitStep> s_wait = std::make_shared<WaitStep>(250);
  //   std::shared_ptr<WaitStep> s_wait_2 = std::make_shared<WaitStep>(200);

  //   std::shared_ptr<Action> test_ac = std::make_shared<Action>();
  //   std::shared_ptr<Action> test_ac_2 = std::make_shared<Action>();

  //   test_ac->setSteps({s_PWM, s_ac2, s_ac3, s_wait, s_ac4, s_ac5, s_wait,
  //   s_ac2,
  //                      s_ac3, s_wait, s_ac4, s_wait, s_ac5, s_PWM});

  //   test_ac_2->setSteps(
  //       {s_PWM, s_wait_2, s_ac2, s_wait_2, s_ac5, s_wait_2, s_PWM});

  //   test_ac_2->setSteps(
  //       {s_PWM, s_wait_2, s_ac2, s_ac3, s_wait_2, s_ac4, s_ac5, s_wait_2,
  //       s_PWM});

  //   // test_ac->setSteps({s1a, s2, s4, s6, s8, s3});
  //   delay(2000);
  //   // test_ac->setSteps({s1a, s1b, s2, s4, s6, s8, s3});
  //   test_hand.addAction(test_ac, "test");
  //   test_hand.addAction(test_ac_2, "test_2");
  //   // test_ac->configureAction();

  //   // std::shared_ptr<PatternDRV2605L> reset =
  //   //     std::make_shared<PatternDRV2605L>(48);
  //   // driver_2->setWaveform(0, p_2);
  //   // driver_2->setWait(1, 1000);
  //   // driver_2->setWaveform(2, p_2);
  //   // driver_2->setWaveform(3, reset);
  //   delay(1000);

  //   while (1) {
  //     test_hand.configureAndPlayAction("test_2");

  //     delay(1000);
  //   }

  //   /*
  //       Custom Pulse Width Mudulation that specifies
  //       duration in miliseconds (in this example 100ms and 50ms)
  //       and status (1 = true = ON or 0 = false = OFF)
  //   */
  //   std::vector<ModulationPWM> modulationPWM_1 = {
  //       {100, true}, {50, false}, {100, true},
  //       {50, false}, {100, true}, {50, false},
  //   };

  //   std::shared_ptr<PatternPWM> pattern_1 =
  //       std::make_shared<PatternPWM>(modulationPWM_1);

  //   Serial.print("------------------------------------- \n");

  //   Serial.print("Loop ... \n");
  //   delay(10000);

  while (1) {
    // test_hand.configureAndPlayAction("test_2");

    delay(1000);
  }
}
