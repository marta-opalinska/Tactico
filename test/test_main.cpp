// clang-format off
// Format need to be turned off - Arduino library need to be compiled as the last one 
// Arduino min and max function provides errors for NRF5280 chipset.
#include <unity.h>
#include "Tactico.h"

#include <Arduino.h>

// clang-format on

void setUp(void) {
  // Serial.begin(9600);
}

void tearDown(void) {
  // clean stuff up here
}

void test_default_actuator_name(void) {
  TEST_ASSERT_EQUAL("actuator_", ACTUATOR_DEFAULT_NAME);
}

void test_create_actuators_driver_GPIO(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(8);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(12);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(15);
  std::shared_ptr<ActuatorDriverGPIO> driver_4 =
      std::make_shared<ActuatorDriverGPIO>(17);
  TEST_ASSERT_EQUAL(8, driver_1->getDriverPin());
  TEST_ASSERT_EQUAL(12, driver_2->getDriverPin());
  TEST_ASSERT_EQUAL(15, driver_3->getDriverPin());
  TEST_ASSERT_EQUAL(17, driver_4->getDriverPin());
}

void test_create_actuators_ERM_with_driver_GPIO(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(14);
  std::string s = "ac_1";
  std::shared_ptr<ActuatorERM> ac_1 =
      std::make_shared<ActuatorERM>(driver_1, s);
  //   TEST_ASSERT_EQUAL(driver_1, ac_1->getDriver());
  TEST_ASSERT(driver_1 == ac_1->getDriver());
  TEST_ASSERT("ac_1" == ac_1->m_name);

  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(12);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  TEST_ASSERT(driver_2 == ac_2->getDriver());
  TEST_ASSERT("actuator_2" == ac_1->m_name);
}

void test_start_actuator_ERM(void) {
  int driverPin = PIN_BUTTON3;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  ac_1->start();
  waitForMiliseconds(200);
  setPinModeTactico(driverPin, INPUT);
  TEST_ASSERT_EQUAL(1, digitalRead(driverPin));
}

void test_stop_actuator_ERM(void) {
  int driverPin = PIN_BUTTON3;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  ac_1->start();
  waitForMiliseconds(200);
  ac_1->stop();
  setPinModeTactico(driverPin, INPUT);
  TEST_ASSERT_EQUAL(0, digitalRead(driverPin));
}

void test_swap_driver_GPIO_pin(void) {
  int driverPin = PIN_BUTTON3;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  ac_1->start();
  waitForMiliseconds(200);
  ac_1->stop();
  driverPin = PIN_BUTTON2;
  driver_1->setDriverPin(driverPin);
  ac_1->start();
  waitForMiliseconds(200);
  setPinModeTactico(driverPin, INPUT);
  TEST_ASSERT_EQUAL(HIGH, digitalRead(driverPin));
}

void test_swap_driver(void) {
  int driverPin1 = PIN_BUTTON3;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  int driverPin2 = PIN_BUTTON1;
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);
  driver_2->stopActuator();

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  ac_1->start();
  waitForMiliseconds(200);
  ac_1->stop();

  ac_1->setDriver(driver_2);
  ac_1->start();
  waitForMiliseconds(200);
  setPinModeTactico(driverPin2, INPUT);
  TEST_ASSERT_EQUAL(1, digitalRead(driverPin2));
}

void test_create_haptic_device(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  HapticDevice right_hand({ac_1, ac_2});
  std::vector<std::shared_ptr<IActuator>> deviceActuatorsList =
      right_hand.getActuatorsList();
  std::vector<std::shared_ptr<IActuator>> expectedDeviceActuatorsList = {ac_1,
                                                                         ac_2};
  TEST_ASSERT(expectedDeviceActuatorsList == deviceActuatorsList);
}

void test_add_actuator_to_haptic_device(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(3);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);

  HapticDevice right_hand({ac_1, ac_2});
  right_hand.addActuator(ac_3);
  std::vector<std::shared_ptr<IActuator>> deviceActuatorsList =
      right_hand.getActuatorsList();
  std::vector<std::shared_ptr<IActuator>> expectedDeviceActuatorsList = {
      ac_1, ac_2, ac_3};
  TEST_ASSERT(expectedDeviceActuatorsList == deviceActuatorsList);
}

void test_add_actuators_to_haptic_device(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(3);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);

  HapticDevice right_hand(ac_1);
  right_hand.addActuators({ac_2, ac_3});
  std::vector<std::shared_ptr<IActuator>> deviceActuatorsList =
      right_hand.getActuatorsList();
  std::vector<std::shared_ptr<IActuator>> expectedDeviceActuatorsList = {
      ac_1, ac_2, ac_3};
  TEST_ASSERT(expectedDeviceActuatorsList == deviceActuatorsList);
}

void test_remove_actuators_from_haptic_device(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(3);
  std::shared_ptr<ActuatorDriverGPIO> driver_4 =
      std::make_shared<ActuatorDriverGPIO>(4);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);
  std::shared_ptr<ActuatorERM> ac_4 = std::make_shared<ActuatorERM>(driver_4);

  HapticDevice right_hand({ac_1, ac_2, ac_3, ac_4});
  right_hand.removeActuator(ac_1);
  right_hand.removeActuator(ac_2->m_name);
  right_hand.removeActuator(1);
  std::vector<std::shared_ptr<IActuator>> deviceActuatorsList =
      right_hand.getActuatorsList();
  std::vector<std::shared_ptr<IActuator>> expectedDeviceActuatorsList = {ac_3};
  TEST_ASSERT(expectedDeviceActuatorsList == deviceActuatorsList);
}

void test_remove_haptic_device_clear_actuators_list(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(3);
  std::shared_ptr<ActuatorDriverGPIO> driver_4 =
      std::make_shared<ActuatorDriverGPIO>(4);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);
  std::shared_ptr<ActuatorERM> ac_4 = std::make_shared<ActuatorERM>(driver_4);

  HapticDevice right_hand({ac_1, ac_2, ac_3, ac_4});
  right_hand.clearActuatorsList();
  std::vector<std::shared_ptr<IActuator>> deviceActuatorsList =
      right_hand.getActuatorsList();
  std::vector<std::shared_ptr<IActuator>> expectedDeviceActuatorsList = {};
  TEST_ASSERT(expectedDeviceActuatorsList == deviceActuatorsList);
}
/////////////////////////////////////////////////////////

void test_haptic_device_start_actuators(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(3);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);

  driver_1->stopActuator();
  driver_2->stopActuator();
  driver_3->stopActuator();

  HapticDevice right_hand({ac_1, ac_2, ac_3});

  right_hand.startActuators();

  setPinModeTactico(1, INPUT);
  setPinModeTactico(2, INPUT);
  setPinModeTactico(3, INPUT);

  TEST_ASSERT_EQUAL(1, digitalRead(1));
  TEST_ASSERT_EQUAL(1, digitalRead(2));
  TEST_ASSERT_EQUAL(1, digitalRead(3));
}

void test_haptic_device_stop_actuators(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(3);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);

  HapticDevice right_hand({ac_1, ac_2, ac_3});

  right_hand.startActuators();
  waitForMiliseconds(200);
  right_hand.stopActuators();

  setPinModeTactico(1, INPUT);
  setPinModeTactico(2, INPUT);
  setPinModeTactico(3, INPUT);

  TEST_ASSERT_EQUAL(0, digitalRead(1));
  TEST_ASSERT_EQUAL(0, digitalRead(2));
  TEST_ASSERT_EQUAL(0, digitalRead(3));
}

// void test_wait_step_create(void) {
//     IStep s = StepWait(500);

// }

void test_actuator_step_start(void) {
  int driverPin = 1;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  StepActuator s1 = StepActuator(ac_1, true);

  driver_1->stopActuator();
  waitForMiliseconds(200);
  s1.play();
  setPinModeTactico(driverPin, INPUT);

  TEST_ASSERT_EQUAL(1, digitalRead(driverPin));
}

void test_actuator_step_stop(void) {
  int driverPin = 1;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  StepActuator s1 = StepActuator(ac_1, false);

  driver_1->startActuator();
  waitForMiliseconds(200);
  s1.play();
  setPinModeTactico(driverPin, INPUT);

  TEST_ASSERT_EQUAL(0, digitalRead(driverPin));
}

void test_action_create(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  ac_1->stop();
  ac_2->start();

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::shared_ptr<StepActuator> s1 = std::make_shared<StepActuator>(ac_1, true);
  std::shared_ptr<StepWait> s2 = std::make_shared<StepWait>(500);
  std::shared_ptr<StepActuator> s3 =
      std::make_shared<StepActuator>(ac_2, false);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);

  std::vector<std::shared_ptr<IStep>> stepsList = a_left->getSteps();
  std::vector<std::shared_ptr<IStep>> expectedStepsList = {s1, s2, s3};
  TEST_ASSERT(expectedStepsList == stepsList);
}

void test_action_set_steps(void) {
  int driverPin1 = 1;
  int driverPin2 = 2;
  int driverPin3 = 3;

  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);
  std::shared_ptr<ActuatorDriverGPIO> driver_3 =
      std::make_shared<ActuatorDriverGPIO>(driverPin3);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);

  ac_1->stop();
  ac_2->start();
  ac_3->start();

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::shared_ptr<StepActuator> s1 = std::make_shared<StepActuator>(ac_1, true);
  std::shared_ptr<StepWait> s2 = std::make_shared<StepWait>(500);
  std::shared_ptr<StepActuator> s3 =
      std::make_shared<StepActuator>(ac_2, false);
  std::shared_ptr<StepActuator> s4 =
      std::make_shared<StepActuator>(ac_3, false);

  a_left->setSteps({s1, s2, s3, s4});

  std::vector<std::shared_ptr<IStep>> stepsList = a_left->getSteps();
  std::vector<std::shared_ptr<IStep>> expectedStepsList = {s1, s2, s3, s4};
  TEST_ASSERT(expectedStepsList == stepsList);
}

void test_action_remove_step(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  ac_1->stop();
  ac_2->start();

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::shared_ptr<StepActuator> s1 = std::make_shared<StepActuator>(ac_1, true);
  std::shared_ptr<StepWait> s2 = std::make_shared<StepWait>(500);
  std::shared_ptr<StepActuator> s3 =
      std::make_shared<StepActuator>(ac_2, false);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);
  a_left->removeStep(1);
  a_left->removeStep(0);
  a_left->addStep(s2);
  a_left->addStep(s1);

  std::vector<std::shared_ptr<IStep>> stepsList = a_left->getSteps();
  std::vector<std::shared_ptr<IStep>> expectedStepsList = {s3, s2, s1};
  TEST_ASSERT(expectedStepsList == stepsList);
}

void test_action_play(void) {
  int driverPin1 = 1;
  int driverPin2 = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  ac_1->stop();
  ac_2->start();

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::shared_ptr<StepActuator> s1 = std::make_shared<StepActuator>(ac_1, true);
  std::shared_ptr<StepWait> s2 = std::make_shared<StepWait>(500);
  std::shared_ptr<StepActuator> s3 =
      std::make_shared<StepActuator>(ac_2, false);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);
  a_left->play();

  setPinModeTactico(driverPin1, INPUT);
  setPinModeTactico(driverPin2, INPUT);

  TEST_ASSERT_EQUAL(1, digitalRead(driverPin1));
  TEST_ASSERT_EQUAL(0, digitalRead(driverPin2));
}

void test_dd(void) {}
void test_dddd(void) {}
void test_dddww(void) {}

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  waitForMiliseconds(2000);

  //  Begin unit testing
  UNITY_BEGIN();  // IMPORTANT LINE!
  RUN_TEST(test_default_actuator_name);
  RUN_TEST(test_create_actuators_driver_GPIO);
  RUN_TEST(test_start_actuator_ERM);
  RUN_TEST(test_stop_actuator_ERM);
  RUN_TEST(test_swap_driver_GPIO_pin);
  RUN_TEST(test_swap_driver);
  RUN_TEST(test_create_haptic_device);
  RUN_TEST(test_add_actuator_to_haptic_device);
  RUN_TEST(test_add_actuators_to_haptic_device);
  RUN_TEST(test_remove_actuators_from_haptic_device);
  RUN_TEST(test_remove_haptic_device_clear_actuators_list);
  RUN_TEST(test_haptic_device_start_actuators);
  RUN_TEST(test_haptic_device_stop_actuators);
  RUN_TEST(test_actuator_step_start);
  RUN_TEST(test_actuator_step_stop);
  /////////////////////////////////////////
  RUN_TEST(test_action_create);
  RUN_TEST(test_action_set_steps);
  RUN_TEST(test_action_play);
  RUN_TEST(test_action_remove_step);
}

// uint8_t i = 0;
// uint8_t max_blinks = 5;

void loop() {
  //   RUN_TEST(test_create_actuator);
  //   if (i < max_blinks)
  //   {
  //     RUN_TEST(test_led_state_high);
  //     waitformiliseconds(500);
  //     RUN_TEST(test_led_state_low);
  //     waitformiliseconds(500);
  //     i++;
  //   }
  //   else if (i == max_blinks)
  //   {
  UNITY_END();  // stop unit testing
  //   }
}