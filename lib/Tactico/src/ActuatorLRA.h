#pragma once
#include <Interfaces/IActuator.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Interfaces/IPattern.h"
#include "PatternPWM.h"
#include "Step.h"

#ifndef ACTUATOR_LRA_DEFAULT_NAME
#define ACTUATOR_LRA_DEFAULT_NAME "actuatorLRA_"
#endif

class PatternPWM;

/**
 * @class ActuatorLRA
 * @brief Class that stores information and methods for ERM actuator type. It
 * implements IActuator interface.
 * @implements IActuator
 * @param m_driver requirered parameter, links the actuator with the driver
 * @param m_name optional parameter, actuator custom name
 *
 */
class ActuatorLRA : public IActuator {
 protected:
  static int nextID;

 public:
  ActuatorLRA() = delete;
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

  bool play(std::shared_ptr<IPattern> pattern);
  void configureDriver();
  /**
   * @brief Assign Driver object to the actuator
   *
   * @param driver ActuatorDriver object to assign
   */
  void setDriver(std::shared_ptr<IActuatorDriver> driver);
  std::shared_ptr<IActuatorDriver> getDriver();
  ActuatorType getType();
  ~ActuatorLRA() = default;
};
