// clang-format off
// Format need to be turned off - Arduino library need to be compiled as the last one 
// Arduino min and max function provides errors for NRF5280 chipset.
#include <Arduino.h>
#undef min
#undef max

#include <unity.h>
#include "Tactico.h"
// clang-format on

void setUp(void) {
  // Serial.begin(9600);
}

void tearDown(void) {
  // clean stuff up here
}

void test_ERM_default_actuator_name(void) {
  TEST_ASSERT_EQUAL("actuatorERM_", ACTUATOR_ERM_DEFAULT_NAME);
}

void test_LRA_default_actuator_name(void) {
  TEST_ASSERT_EQUAL("actuatorLRA_", ACTUATOR_LRA_DEFAULT_NAME);
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
  TEST_ASSERT_EQUAL(8, driver_1->getPin());
  TEST_ASSERT_EQUAL(12, driver_2->getPin());
  TEST_ASSERT_EQUAL(15, driver_3->getPin());
  TEST_ASSERT_EQUAL(17, driver_4->getPin());
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

void test_ERM_actuator_step_start(void) {
  int driverPin = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);

  ActuatorStepImpl s1 = ActuatorStepImpl(ac_1, p_1);

  setPinStatusTactico(2, 0);
  waitFor(200);
  s1.play();
  setPinModeTactico(driverPin, INPUT);

  TEST_ASSERT_EQUAL(1, digitalRead(driverPin));
}

void test_ERM_actuator_step_stop(void) {
  int driverPin = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::vector<ModulationPWM> mod_1 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);

  ActuatorStepImpl s1 = ActuatorStepImpl(ac_1, p_1);

  setPinStatusTactico(2, 1);
  waitFor(200);
  s1.play();
  setPinModeTactico(driverPin, INPUT);

  TEST_ASSERT_EQUAL(0, digitalRead(driverPin));
}

void test_swap_driver_GPIO_pin(void) {
  int driverPin = 4;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);

  driverPin = 3;

  driver_1->setPin(driverPin);
  setPinStatusTactico(3, 0);
  ac_1->play(p_1);
  waitFor(200);
  setPinModeTactico(driverPin, INPUT);

  TEST_ASSERT_EQUAL(HIGH, digitalRead(driverPin));
}

void test_ERM_swap_driver(void) {
  int driverPin1 = 4;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  int driverPin2 = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);
  std::vector<ModulationPWM> mod_1 = {{200, true}, {200, false}, {200, true}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);

  setPinStatusTactico(driverPin1, 0);
  setPinStatusTactico(driverPin2, 0);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  ac_1->play(p_1);

  ac_1->setDriver(driver_2);
  ac_1->play(p_1);

  setPinModeTactico(driverPin2, INPUT);
  TEST_ASSERT_EQUAL(1, digitalRead(driverPin2));
}

void test_action_create(void) {
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(2);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  setPinStatusTactico(1, 0);
  setPinStatusTactico(2, 1);

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);

  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);

  std::vector<std::shared_ptr<IStep>> stepsList = a_left->getSteps();
  std::vector<std::shared_ptr<IStep>> expectedStepsList = {s1, s2, s3};
  TEST_ASSERT(expectedStepsList == stepsList);
}

void test_action_set_steps(void) {
  int driverPin1 = 4;
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

  setPinStatusTactico(driverPin1, 0);
  setPinStatusTactico(driverPin2, 1);
  setPinStatusTactico(driverPin3, 1);

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);

  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);
  std::shared_ptr<ActuatorStepImpl> s4 =
      std::make_shared<ActuatorStepImpl>(ac_3, p_2);

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

  setPinStatusTactico(1, 0);
  setPinStatusTactico(2, 1);

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);

  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);

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
  int driverPin1 = 4;
  int driverPin2 = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);

  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  setPinStatusTactico(driverPin1, 0);
  setPinStatusTactico(driverPin2, 1);

  std::shared_ptr<Action> a_left = std::make_shared<Action>();

  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);

  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);
  a_left->play();

  setPinModeTactico(driverPin1, INPUT);
  setPinModeTactico(driverPin2, INPUT);

  TEST_ASSERT_EQUAL(1, digitalRead(driverPin1));
  TEST_ASSERT_EQUAL(0, digitalRead(driverPin2));
}

void test_haptic_device_create(void) {
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

void test_haptic_device_add_actuator(void) {
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

void test_haptic_device_add_actuators(void) {
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

void test_haptic_device_remove_actuators(void) {
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

void test_haptic_device_clear_actuators_list(void) {
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

void test_haptic_device_add_actions(void) {
  int driverPin1 = 4;
  int driverPin2 = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  setPinStatusTactico(driverPin1, 0);
  setPinStatusTactico(driverPin2, 1);

  std::shared_ptr<Action> a_left = std::make_shared<Action>();
  std::shared_ptr<Action> a_right = std::make_shared<Action>();
  std::shared_ptr<Action> a_center = std::make_shared<Action>();
  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);
  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);

  a_right->addStep(s3);
  a_right->addStep(s2);
  a_right->addStep(s1);

  a_center->addStep(s1);
  a_center->addStep(s3);

  HapticDevice right_hand({ac_1, ac_2});
  right_hand.addAction(a_left, "a_left");
  std::map<std::string, std::shared_ptr<Action>> additionalActions;
  additionalActions["a_right"] = a_right;
  additionalActions["a_center"] = a_center;
  right_hand.addActions(additionalActions);

  std::map<std::string, std::shared_ptr<Action>> actionList =
      right_hand.getActions();
  std::map<std::string, std::shared_ptr<Action>> expectedActionList;
  expectedActionList["a_left"] = a_left;
  expectedActionList["a_right"] = a_right;
  expectedActionList["a_center"] = a_center;
  TEST_ASSERT(expectedActionList == actionList);
}

void test_haptic_device_remove_actions(void) {
  int driverPin1 = 4;
  int driverPin2 = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  setPinStatusTactico(driverPin1, 0);
  setPinStatusTactico(driverPin2, 1);
  HapticDevice right_hand({ac_1, ac_2});

  std::shared_ptr<Action> a_left = std::make_shared<Action>();
  std::shared_ptr<Action> a_right = std::make_shared<Action>();
  std::shared_ptr<Action> a_center = std::make_shared<Action>();
  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);
  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);

  a_right->addStep(s3);
  a_right->addStep(s2);
  a_right->addStep(s1);

  a_center->addStep(s1);
  a_center->addStep(s3);

  std::map<std::string, std::shared_ptr<Action>> additionalActions;
  additionalActions["a_center"] = a_center;
  additionalActions["a_left"] = a_left;
  additionalActions["a_right"] = a_right;
  right_hand.addActions(additionalActions);

  right_hand.removeAction("a_center");

  std::map<std::string, std::shared_ptr<Action>> actionList =
      right_hand.getActions();
  std::map<std::string, std::shared_ptr<Action>> expectedActionList;
  expectedActionList["a_left"] = a_left;
  expectedActionList["a_right"] = a_right;
  TEST_ASSERT(expectedActionList == actionList);

  right_hand.removeAction("a_right");
  actionList = right_hand.getActions();
  expectedActionList.erase("a_right");
  TEST_ASSERT(expectedActionList == actionList);
}

void test_haptic_device_clear_actions(void) {
  int driverPin1 = 4;
  int driverPin2 = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

  setPinStatusTactico(driverPin1, 0);
  setPinStatusTactico(driverPin2, 1);
  HapticDevice right_hand({ac_1, ac_2});

  std::shared_ptr<Action> a_left = std::make_shared<Action>();
  std::shared_ptr<Action> a_right = std::make_shared<Action>();
  std::shared_ptr<Action> a_center = std::make_shared<Action>();
  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);
  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);

  a_right->addStep(s3);
  a_right->addStep(s2);
  a_right->addStep(s1);

  a_center->addStep(s1);
  a_center->addStep(s3);

  std::map<std::string, std::shared_ptr<Action>> additionalActions;
  additionalActions["a_center"] = a_center;
  additionalActions["a_left"] = a_left;
  additionalActions["a_right"] = a_right;
  right_hand.addActions(additionalActions);

  std::map<std::string, std::shared_ptr<Action>> actionList =
      right_hand.getActions();
  std::map<std::string, std::shared_ptr<Action>> expectedActionList;
  expectedActionList["a_left"] = a_left;
  expectedActionList["a_right"] = a_right;
  expectedActionList["a_center"] = a_center;
  TEST_ASSERT(expectedActionList == actionList);

  right_hand.clearActions();
  actionList = right_hand.getActions();
  expectedActionList.clear();
  TEST_ASSERT(expectedActionList == actionList);
}

void test_haptic_device_play_action(void) {
  int driverPin1 = 4;
  int driverPin2 = 2;
  std::shared_ptr<ActuatorDriverGPIO> driver_1 =
      std::make_shared<ActuatorDriverGPIO>(driverPin1);
  std::shared_ptr<ActuatorDriverGPIO> driver_2 =
      std::make_shared<ActuatorDriverGPIO>(driverPin2);
  std::shared_ptr<ActuatorERM> ac_1 = std::make_shared<ActuatorERM>(driver_1);
  std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);
  setPinStatusTactico(driverPin1, 0);
  setPinStatusTactico(driverPin2, 1);
  HapticDevice right_hand({ac_1, ac_2});

  std::shared_ptr<Action> a_left = std::make_shared<Action>();
  std::shared_ptr<Action> a_right = std::make_shared<Action>();
  std::vector<ModulationPWM> mod_1 = {{200, true}};
  std::vector<ModulationPWM> mod_2 = {{200, false}};
  std::shared_ptr<IPattern> p_1 = std::make_shared<PatternPWM>(mod_1);
  std::shared_ptr<IPattern> p_2 = std::make_shared<PatternPWM>(mod_2);
  std::shared_ptr<ActuatorStepImpl> s1 =
      std::make_shared<ActuatorStepImpl>(ac_1, p_1);
  std::shared_ptr<WaitStepImpl> s2 = std::make_shared<WaitStepImpl>(500);
  std::shared_ptr<ActuatorStepImpl> s3 =
      std::make_shared<ActuatorStepImpl>(ac_2, p_2);

  a_left->addStep(s1);
  a_left->addStep(s2);
  a_left->addStep(s3);

  a_right->addStep(s3);
  a_right->addStep(s2);
  a_right->addStep(s1);

  std::map<std::string, std::shared_ptr<Action>> additionalActions;
  additionalActions["a_left"] = a_left;

  right_hand.addActions(additionalActions);
  right_hand.playAction("a_left");

  setPinModeTactico(driverPin1, INPUT);
  setPinModeTactico(driverPin2, INPUT);

  TEST_ASSERT_EQUAL(1, digitalRead(driverPin1));
  TEST_ASSERT_EQUAL(0, digitalRead(driverPin2));
}

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  waitFor(2000);

  //  Begin unit testing
  UNITY_BEGIN();  // IMPORTANT LINE!

  RUN_TEST(test_ERM_default_actuator_name);
  RUN_TEST(test_LRA_default_actuator_name);

  // ERM actuator with GPIO driver
  RUN_TEST(test_create_actuators_driver_GPIO);
  RUN_TEST(test_ERM_actuator_step_start);
  RUN_TEST(test_ERM_actuator_step_stop);
  RUN_TEST(test_swap_driver_GPIO_pin);
  RUN_TEST(test_ERM_swap_driver);

  // Testing Actions and steps combination
  RUN_TEST(test_action_create);
  RUN_TEST(test_action_set_steps);
  RUN_TEST(test_action_play);
  RUN_TEST(test_action_remove_step);

  // Testign haptic device functionsS
  RUN_TEST(test_haptic_device_create);
  RUN_TEST(test_haptic_device_add_actuator);
  RUN_TEST(test_haptic_device_add_actuators);
  RUN_TEST(test_haptic_device_remove_actuators);
  RUN_TEST(test_haptic_device_clear_actuators_list);
  RUN_TEST(test_haptic_device_add_actions);
  RUN_TEST(test_haptic_device_remove_actions);
  RUN_TEST(test_haptic_device_clear_actions);
  RUN_TEST(test_haptic_device_play_action);
}

void loop() {
  UNITY_END();  // stop unit testing
}
