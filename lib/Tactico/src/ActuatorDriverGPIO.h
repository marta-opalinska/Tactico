/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuatorDriver.h>
#include <PatternPWM.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

class IPattern;
class PatternPWM;

/**
 * @class ActuatorDriverGPIO
 * @brief Class that stores information and methods for Actuator Driver
 * controlled using GPI pin.
 * @implements IActuatorDriver
 */
class ActuatorDriverGPIO : public IActuatorDriver {
 protected:
  /**
   * GPIO pin to controll assigned Actuator
   */
  int m_GPIO_pin;

  /**
   * Set m_GPIO_pin HIGH.
   */
  void setGPIOHigh();

  /**
   * Set m_GPIO_pin LOW.
   */
  void setGPIOLow();

 public:
  /**
   * @brief Construct a new Actuator Driver GPIO
   *
   * @param GPIO_pin pin to controll assigned Actuator
   */
  explicit ActuatorDriverGPIO(int GPIO_pin);
  ActuatorDriverGPIO() = delete;
  ~ActuatorDriverGPIO() = default;

  /**
   * @brief Initiate the driver - GPIO pin
   *
   */
  void init();

  /**
   * @brief Play the pattern supported by the driver.
   *
   * @param pattern pattern to play
   * @return true
   * @return false
   */
  bool play(std::shared_ptr<IPattern> pattern);

  /**
   * @brief Test the motor vibration.
   *
   */
  void test();

  /**
   * @brief Get the control GPIO pin
   *
   * @return int
   */
  int getPin();

  /**
   * @brief Set the control GPIO pin
   *
   * @param new_GPIO GPIO pin
   */
  void setPin(int new_GPIO);

  /**
   * @brief No configuration to reset for GPIO driver. Only for drivers with
   * preconfiguration setup.
   *
   */
  void resetConfiguration();

  /**
   * @brief Get the ActuatorDriverType of the object
   *
   * @return ActuatorDriverType
   */
  ActuatorDriverType getType();
};
