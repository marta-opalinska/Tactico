/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>
#include <Interfaces/IStep.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "PatternPWM.h"

#ifndef ACTUATOR_ERM_DEFAULT_NAME
#define ACTUATOR_ERM_DEFAULT_NAME "actuatorERM_"
#endif

class PatternPWM;

/**
 * @class ActuatorERM
 * @brief Class that stores information and methods for ERM actuator type. It
 * implements IActuator interface.
 * @implements IActuator
 *
 */
class ActuatorERM : public IActuator {
 protected:
  /**
   * Unique ID seter
   */
  static int nextID;

 public:
  ActuatorERM() = delete;
  ~ActuatorERM() = default;

  /**
   * @brief Construct a new ERM Actuator object
   *
   * @param driver required parameter, ActuatorDriver object to control the
   * physical interface
   * @param ratedVoltage the standard DC voltage for the actuator
   * @param overdriveVoltage the maximum allowable DC voltage
   */
  explicit ActuatorERM(std::shared_ptr<IActuatorDriver> driver,
                       float ratedVoltage, float overdriveVoltage);
  /**
   * @brief Construct a new ERM Actuator object with a custom name
   *
   * @param driver required parameter, ActuatorDriver object to control the
   * physical interface
   * @param ratedVoltage the standard DC voltage for the actuator
   * @param overdriveVoltage the maximum allowable DC voltage
   * @param name custom Actuator name
   */
  ActuatorERM(std::shared_ptr<IActuatorDriver> driver, float ratedVoltage,
              float overdriveVoltage, const std::string &name);

  /**
   * @brief Play the pattern supported by the actuator.
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
   * @brief Configure the actuator's driver.
   *
   */
  void configDriver();
  /**
   * @brief Assign Driver object to the Actuator
   *
   * @param driver ActuatorDriver object to assign
   */
  void setDriver(std::shared_ptr<IActuatorDriver> driver);

  /**
   * @brief Get the actuator's Driver
   *
   * @return std::shared_ptr<IActuatorDriver>
   */
  std::shared_ptr<IActuatorDriver> getDriver();

  /**
   * @brief Get the ActuatorType of the object
   *
   * @return ActuatorType
   */
  ActuatorType getType();
};
