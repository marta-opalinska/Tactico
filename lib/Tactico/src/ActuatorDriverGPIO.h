#pragma once
#include <Interfaces/IActuatorDriver.h>

#include <string>

#include "HardwareLayer.h"

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
  void setHighGPIO();
  void setLowGPIO();

 public:
  explicit ActuatorDriverGPIO(int GPIO_pin);
  ActuatorDriverGPIO() = delete;
  ~ActuatorDriverGPIO() = default;
  void initDriver();
  void startActuator();
  void stopActuator();
  int getDriverPin();
  void setDriverPin(int new_GPIO);
  // play(PatternPWM pattern);
  // void playInterval(int time);
};
