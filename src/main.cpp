
// Tactico framework imports
#include <Tactico.h>

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

// #include <iostream>
// #include "Framework/ActuatorDriverGPIO.h"
// #include "Framework/Actuator.h"
// #include <string.h>
// #include <string>
// #undef min
// #undef max

#include "Arduino.h"
#undef min
#undef max

// #include <functional>
int setupDone;

void setup() {
  Serial.begin(9600);
  setupDone = false;

  // pinMode(LED_BUILTIN, OUTPUT); // set pin as output

  Serial.print("------------------------------------- \n");
}

void loop() {
  delay(1000);
  if (!setupDone) {
    Serial.print("------------------------------------- \n");
    Serial.print("Initiating Drivers... \n");

    std::shared_ptr<ActuatorDriverGPIO> driver_1 =
        std::make_shared<ActuatorDriverGPIO>(8);
    std::shared_ptr<ActuatorDriverGPIO> driver_2 =
        std::make_shared<ActuatorDriverGPIO>(12);
    std::shared_ptr<ActuatorDriverGPIO> driver_3 =
        std::make_shared<ActuatorDriverGPIO>(15);
    std::shared_ptr<ActuatorDriverGPIO> driver_4 =
        std::make_shared<ActuatorDriverGPIO>(17);
    Serial.print("Iniatiation of drivers done. \n");
    std::string s = "ac_1";

    // ActuatorERM ac_1(driver_1,s);
    // driver_1->e
    std::shared_ptr<ActuatorERM> ac_1 =
        std::make_shared<ActuatorERM>(driver_1, s);
    driver_1->setDriverPin(10);

    std::shared_ptr<ActuatorERM> ac_3 = std::make_shared<ActuatorERM>(driver_3);
    std::shared_ptr<ActuatorERM> ac_2 = std::make_shared<ActuatorERM>(driver_2);

    // ActuatorERM ac_2(driver_2);
    // ActuatorERM ac_3(driver_3);
    HapticDevice right_hand({ac_1, ac_2});
    // Serial.print("Starting RIGHT HAND. \n");
    // right_hand.addActuator(ac_3);
    // right_hand.startActuators();
    // delay(500);
    // Serial.print("Stoping RIGHT HAND. \n");
    // right_hand.stopActuators();
    // ac_3->setDriver(driver_4);
    // delay(500);
    // Serial.print("Starting RIGHT HAND. \n");
    // right_hand.startActuators();
    // delay(500);
    // Serial.print("Stoping RIGHT HAND. \n");
    // right_hand.stopActuators();

    // delay(500);

    // right_hand.removeActuator("ac_1");
    // right_hand.removeActuator(&ac_2);
    // Serial.print("Starting RIGHT HAND. \n");
    // right_hand.startActuators();
    // delay(500);
    // Serial.print("Stoping RIGHT HAND. \n");
    // right_hand.stopActuators();

    // right_hand.addActuator(&ac_1);
    // // right_hand.swapActuator(&ac_3, &ac_2);
    // Serial.print("Before swap:  \n");
    // Serial.print("Starting RIGHT HAND. \n");
    // right_hand.startActuators();
    // delay(500);
    // Serial.print("Stoping RIGHT HAND. \n");
    // right_hand.stopActuators();

    std::shared_ptr<Action> left = std::make_shared<Action>();
    left->addStep(ac_1, true);
    left->addWait(500);
    left->addStep(ac_2, true);
    left->addWait(500);
    left->addStep(ac_1, false);
    left->addStep(ac_2, false);

    right_hand.addAction(left, "left");

    right_hand.playAction("left");

    // left.play();

    // std::vector<ModulationPWM> mod_1{{200,true}, {200, false}, {100, true},
    // {100, false}}; PatternPWM p_1(mod_1); std::shared_ptr<ActuatorERM>
    // ac_1_ptr = std::make_shared<ActuatorERM>(ac_1); p_1.play(ac_1_ptr);

    setupDone = true;
  }
  Serial.print("------------------------------------- \n");

  Serial.print("Loop ... \n");
  delay(15000);
}
