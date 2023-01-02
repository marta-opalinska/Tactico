/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuatorDriver.h>
#include <PatternPWM.h>

#include <memory>
#include <string>
// clang-format off
#include "HardwareLayer.h"
// clang-format on

class IPattern;
class PatternPWM;

/**
 * @class ActuatorDriverGPIO
 * @brief Class that stores information and methods for Actuator Driver
 * controlled using GPI pin
 * @implements IActuatorDriver
 * @param m_GPIO_pin GPIO pin of the assigned Actuator
 */
class ActuatorDriverGPIO : public IActuatorDriver {
 protected:
  int m_GPIO_pin;
  void setGPIOHigh();
  void setGPIOLow();

 public:
  explicit ActuatorDriverGPIO(int GPIO_pin);
  ActuatorDriverGPIO() = delete;
  ~ActuatorDriverGPIO() = default;
  void init();
  bool play(std::shared_ptr<IPattern> pattern);
  void test();
  int getPin();
  void setPin(int new_GPIO);
  ActuatorDriverType getType();
};
