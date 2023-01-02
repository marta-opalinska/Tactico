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

#ifndef ACTUATOR_LRA_DEFAULT_NAME
#define ACTUATOR_LRA_DEFAULT_NAME "actuatorLRA_"
#endif

class PatternPWM;

/**
 * @class ActuatorLRA
 * @brief Class that stores information and methods for LRA actuator type. It
 * implements IActuator interface.
 * @implements IActuator
 *
 */
class ActuatorLRA : public IActuator {
 protected:
  /**
   *  Unique ID seter
   */
  static int nextID;

 public:
  ActuatorLRA() = delete;
  ~ActuatorLRA() = default;
  /**
   * LRA actuator resonant freqency
   */
  int m_resonantFrequency;

  /**
   * @brief Construct a new LRA Actuator object
   *
   * @param driver required parameter, ActuatorDriver object to control the
   * physical interface
   * @param ratedVoltage the standard DC voltage for the actuator
   * @param overdriveVoltage the maximum allowable DC voltage
   * @param resonantFrequency the LRA actuator resonant frequency (can be found
   * in the datasheet)
   *
   */
  explicit ActuatorLRA(std::shared_ptr<IActuatorDriver> driver,
                       float ratedVoltage, float overdriveVoltage,
                       int resonantFrequency);

  /**
   * @brief Construct a new LRA Actuator object with a custom name
   *
   * @param driver required parameter, ActuatorDriver object to control the
   * physical interface
   * @param ratedVoltage the standard DC voltage for the actuator
   * @param overdriveVoltage the maximum allowable DC voltage
   * @param resonantFrequency the LRA actuator resonant frequency (can be found
   * in the datasheet)
   * @param name custom Actuator name
   */
  ActuatorLRA(std::shared_ptr<IActuatorDriver> driver, float ratedVoltage,
              float overdriveVoltage, int resonantFrequency,
              const std::string &name);

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
