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

// #include <functional>
int setupDone;

void setup() {
  Serial.begin(9600);
  setupDone = false;
  //   while (!Serial) {
  //     ;  // wait for serial port to connect. Needed for native USB
  //   }

  // pinMode(LED_BUILTIN, OUTPUT); // set pin as output
  delay(2000);
  Serial.print("------------------------------------- \n");
}

void loop() {
  if (!setupDone) {
    int driverPin1 = ARDUINNO_NANO_RED;
    // driverPin1 = PIN_BUTTON1;
    // driverPin1 = 22;
    // int driverPin2 = 2;
    std::shared_ptr<ActuatorDriverGPIO> driver_1 =
        std::make_shared<ActuatorDriverGPIO>(driverPin1);

    std::shared_ptr<ActuatorERM> ac_1 =
        std::make_shared<ActuatorERM>(driver_1, 2, 3);
    // std::shared_ptr<ActuatorERM> ac_2 =
    // std::make_shared<ActuatorERM>(driver_2);
    HapticDevice right_hand(ac_1);

    std::shared_ptr<Action> a_left = std::make_shared<Action>();
    std::shared_ptr<Action> a_right = std::make_shared<Action>();
    std::vector<ModulationPWM> mod_1 = {
        {100, true}, {50, false}, {40, true}, {30, false}, {20, true}};
    // std::vector<ModulationPWM> mod_2 = {{200, false}};
    std::shared_ptr<PatternPWM> p_1 = std::make_shared<PatternPWM>(mod_1);

    ac_1->play(p_1);

    int driverGoPin2 = 12;
    // driverGoPin2 = PIN_LED1;
    std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_2 =
        std::make_shared<ActuatorDriverDRV2605LEVM>(0, driverGoPin2);
    std::shared_ptr<ActuatorLRA> ac_2 =
        // std::make_shared<ActuatorLRA>(driver_2, 2.5, 2.7, 170, "myLRA");
        std::make_shared<ActuatorLRA>(driver_2, 2, 2.5, 170, "myLRA");

    std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_3 =
        std::make_shared<ActuatorDriverDRV2605LEVM>(1, driverGoPin2);
    std::shared_ptr<ActuatorERM> ac_3 =
        std::make_shared<ActuatorERM>(driver_3, 2, 2.5, "myERM");

    std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_4 =
        std::make_shared<ActuatorDriverDRV2605LEVM>(2, driverGoPin2);
    std::shared_ptr<ActuatorLRA> ac_4 =
        std::make_shared<ActuatorLRA>(driver_4, 2.0, 2.5, 170, "myLRA_2");

    std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_5 =
        std::make_shared<ActuatorDriverDRV2605LEVM>(3, driverGoPin2);
    std::shared_ptr<ActuatorERM> ac_5 =
        std::make_shared<ActuatorERM>(driver_5, 2, 2.5, "myERM_2");

/*
All in-build effect available for the DRV2605L can be found in DRV2605L_EFFECTS.h file
*/
    std::shared_ptr<PatternDRV2605L> p_2 =
        std::make_shared<PatternDRV2605L>(STRONG_CLICK_30);

    HapticDevice test_hand({ac_1, ac_2, ac_3, ac_4, ac_5});

    test_hand.testActuators();

    setPinStatusTactico(driverPin1, HIGH);

    std::shared_ptr<ActuatorStep> s_ac2 =
        std::make_shared<ActuatorStep>(ac_2, p_2, true);
    std::shared_ptr<ActuatorStep> s_ac3 =
        std::make_shared<ActuatorStep>(ac_3, p_2, true);
    std::shared_ptr<ActuatorStep> s_ac4 =
        std::make_shared<ActuatorStep>(ac_4, p_2, true);
    std::shared_ptr<ActuatorStep> s_ac5 =
        std::make_shared<ActuatorStep>(ac_5, p_2, true);

    std::shared_ptr<ActuatorStep> s_PWM =
        std::make_shared<ActuatorStep>(ac_1, p_1);

    std::shared_ptr<WaitStep> s_wait = std::make_shared<WaitStep>(250);
    std::shared_ptr<WaitStep> s_wait_2 = std::make_shared<WaitStep>(200);

    std::shared_ptr<Action> test_ac = std::make_shared<Action>();
    std::shared_ptr<Action> test_ac_2 = std::make_shared<Action>();

    test_ac->setSteps({s_PWM, s_ac2, s_ac3, s_wait, s_ac4, s_ac5, s_wait, s_ac2,
                       s_ac3, s_wait, s_ac4, s_wait, s_ac5, s_PWM});

    test_ac_2->setSteps(
        {s_PWM, s_wait_2, s_ac2, s_wait_2, s_ac5, s_wait_2, s_PWM});

    test_ac_2->setSteps({s_PWM, s_wait_2, s_ac2, s_ac3, s_wait_2, s_ac4, s_ac5,
                         s_wait_2, s_PWM});

    // test_ac->setSteps({s1a, s2, s4, s6, s8, s3});
    delay(2000);
    // test_ac->setSteps({s1a, s1b, s2, s4, s6, s8, s3});
    test_hand.addAction(test_ac, "test");
    test_hand.addAction(test_ac_2, "test_2");
    // test_ac->configure();

    // std::shared_ptr<PatternDRV2605L> reset =
    //     std::make_shared<PatternDRV2605L>(48);
    // driver_2->setWaveform(0, p_2);
    // driver_2->setWait(1, 1000);
    // driver_2->setWaveform(2, p_2);
    // driver_2->setWaveform(3, reset);
    delay(1000);

    while (1) {
      test_hand.configureAndPlayAction("test_2");

      delay(1000);
    }

    /*
        Custom Pulse Width Mudulation that specifies
        duration in miliseconds (in this example 100ms and 50ms)
        and status (1 = true = ON or 0 = false = OFF)
    */
    std::vector<ModulationPWM> modulationPWM_1 = {
        {100, true}, {50, false}, {100, true},
        {50, false}, {100, true}, {50, false},
    };

    std::shared_ptr<PatternPWM> pattern_1 =
        std::make_shared<PatternPWM>(modulationPWM_1);

    // test_hand.configureAndPlayAction("test");

    // delay(3000);

    // delay(5000);

    // test_hand.configureAndPlayAction("test");

    // test_ac->configureAndPlay();

    // driver_4->play(p_2);

    // Serial.print("Pattern 1 finished.");
    // driver_2->play(p_2);
    // Serial.print("Pattern 2 finished.");
    // delay(2000);
    // driver_3->play(p_2);
    // Serial.print("Pattern 3 finished.");

    // delay(3000);

    // std::shared_ptr<PatternDRV2605L> p_2 =8
    //     std::make_shared<PatternDRV2605L>(48);
    // driver_4->play(p_2);
    // delay(2000);
    // driver_4->play(p_2);

    // std::shared_ptr<PatternDRV2605L> p_2 =8
    //     std::make_shared<PatternDRV2605L>(48);
    // driver_5->play(p_2);
    // delay(2000);
    // driver_5->play(p_2);

    // std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);
    // std::shared_ptr<ActuatorStep> s1 =
    //     std::make_shared<ActuatorStep>(ac_1, p_1);
    // std::shared_ptr<WaitStep> s2 = std::make_shared<WaitStep>(1500);
    // std::shared_ptr<ActuatorStep> s3 =
    //     std::make_shared<ActuatorStep>(ac_1, p_1);

    // a_left->addStep(s1);
    // a_left->addStep(s2);
    // a_left->addStep(s3);

    // std::map<std::string, std::shared_ptr<Action>> additionalActions;
    // additionalActions["a_left"] = a_left;

    // right_hand.addActions(additionalActions);
    // right_hand.playAction("a_left");

    setupDone = true;
  }

  // if (!setupDone) {
  //   Serial.print("------------------------------------- \n");
  //   Serial.print("Initiating Drivers... \n");

  //   std::shared_ptr<ActuatorDriverGPIO> driver_1 =
  //       std::make_shared<ActuatorDriverGPIO>(1);
  //   std::shared_ptr<ActuatorDriverGPIO> driver_2 =
  //       std::make_shared<ActuatorDriverGPIO>(12);
  //   std::shared_ptr<ActuatorDriverGPIO> driver_3 =
  //       std::make_shared<ActuatorDriverGPIO>(15);
  //   std::shared_ptr<ActuatorDriverGPIO> driver_4 =
  //       std::make_shared<ActuatorDriverGPIO>(17);
  //   Serial.print("Iniatiation of drivers done. \n");
  //   std::string s = "ac_1";

  //   // ActuatorERM ac_1(driver_1,s);
  //   // driver_1->e
  //   std::shared_ptr<ActuatorERM> ac_1 =
  //       std::make_shared<ActuatorERM>(driver_1, s);
  //   driver_1->setPin(10);

  //   std::shared_ptr<ActuatorERM> ac_3 =
  //   std::make_shared<ActuatorERM>(driver_3); std::shared_ptr<ActuatorERM>
  //   ac_2 = std::make_shared<ActuatorERM>(driver_2);

  //   // ActuatorERM ac_2(driver_2);
  //   // ActuatorERM ac_3(driver_3);
  //   HapticDevice right_hand({ac_1, ac_2});
  //   // Serial.print("Starting RIGHT HAND. \n");
  //   // right_hand.addActuator(ac_3);
  //   // right_hand.startActuators();
  //   // delay(500);
  //   // Serial.print("Stoping RIGHT HAND. \n");
  //   // right_hand.stopActuators();
  //   // ac_3->setDriver(driver_4);
  //   // delay(500);
  //   // Serial.print("Starting RIGHT HAND. \n");
  //   // right_hand.startActuators();
  //   // delay(500);
  //   // Serial.print("Stoping RIGHT HAND. \n");
  //   // right_hand.stopActuators();

  //   // delay(500);

  //   // right_hand.removeActuator("ac_1");
  //   // right_hand.removeActuator(&ac_2);
  //   // Serial.print("Starting RIGHT HAND. \n");
  //   // right_hand.startActuators();
  //   // delay(500);
  //   // Serial.print("Stoping RIGHT HAND. \n");
  //   // right_hand.stopActuators();

  //   // right_hand.addActuator(&ac_1);
  //   // // right_hand.swapActuator(&ac_3, &ac_2);
  //   // Serial.print("Before swap:  \n");
  //   // Serial.print("Starting RIGHT HAND. \n");
  //   // right_hand.startActuators();
  //   // delay(500);
  //   // Serial.print("Stoping RIGHT HAND. \n");
  //   // right_hand.stopActuators();

  //   // std::shared_ptr<Action> left = std::make_shared<Action>();
  //   // left->addStep(ac_1, true);
  //   // left->addWait(500);
  //   // left->addStep(ac_2, true);
  //   // left->addWait(500);
  //   // left->addStep(ac_1, false);
  //   // left->addStep(ac_2, false);

  //   // right_hand.addAction(left, "left");

  //   // right_hand.playAction("left");

  //   // left.play();

  //   // std::vector<ModulationPWM> mod_1{{200,true}, {200, false}, {100,
  //   true},
  //   // {100, false}}; PatternPWM p_1(mod_1); std::shared_ptr<ActuatorERM>
  //   // ac_1_ptr = std::make_shared<ActuatorERM>(ac_1); p_1.play(ac_1_ptr);

  //   setupDone = true;
  // }
  Serial.print("------------------------------------- \n");

  Serial.print("Loop ... \n");
  delay(10000);
}
