/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuatorDriver.h>
#include <Interfaces/IPattern.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

class IPattern;
class IActuatorDriver;

/**
 * @brief Enum of the possible actuator types. It is used for actuator specific
 * methods.
 *
 */
enum ActuatorType { eERM, eLRA };

/**
 * @interface
 * @brief Interface for an actuator - the interface is implemented by
 * ActuatorERM and ActuatorLRA classes
 */
class IActuator {
 protected:
  int id;
  /**
   *  an shared pointer to the implementation of a
   * ActuatorDriver instance
   */
  std::shared_ptr<IActuatorDriver> m_driver;

  /**
   * actuator type based on enum ActuatorType
   */
  ActuatorType m_type;

 public:
  /**
   * actuator name (optional)
   */
  std::string m_name;
  /**
   * actuator's rated voltage
   */
  float m_ratedVoltage;
  /**
   * actuator's peak voltage
   */
  float m_overdriveVoltage;
  /**
   * @brief Construct a new IActuator object
   *
   * @param driver  an shared pointer to the implementation of a ActuatorDriver
   * instance
   * @param ratedVoltage actuator's rated voltage
   * @param overdriveVoltage actuator's peak voltag
   * @param name actuator name (optional)
   */
  IActuator(std::shared_ptr<IActuatorDriver> driver, float ratedVoltage,
            float overdriveVoltage, const std::string &name)
      : m_driver(driver),
        m_name(name),
        m_ratedVoltage(ratedVoltage),
        m_overdriveVoltage(overdriveVoltage) {}
  /**
   * @brief Construct a new IActuator object
   *
   * @param driver  an shared pointer to the implementation of a ActuatorDriver
   * instance
   * @param ratedVoltage actuator's rated voltage
   * @param overdriveVoltage actuator's peak voltag
   */
  explicit IActuator(std::shared_ptr<IActuatorDriver> driver,
                     float ratedVoltage, float overdriveVoltage)
      : m_driver(driver),
        m_ratedVoltage(ratedVoltage),
        m_overdriveVoltage(overdriveVoltage) {}

  /**
   * @brief play a specific pattern on the actuator
   *
   * @param pattern shared pointer to the implementation of a Pattern instance
   * @return true
   * @return false
   */
  virtual bool play(std::shared_ptr<IPattern> pattern) = 0;

  /**
   * @brief play a test pattern to check if the actuator works.
   *
   */
  virtual void test() = 0;

  /**
   * @brief Return a pointer to the actuator's ActuatorDriver
   *
   * @param driver shared pointer to the implementation of an ActuatorDriver
   */
  virtual std::shared_ptr<IActuatorDriver> getDriver() = 0;

  /**
   * @brief Assign a new ActuatorDriver object to the actuator
   *
   * @param driver shared pointer to the implementation of an ActuatorDriver
   */
  virtual void setDriver(std::shared_ptr<IActuatorDriver> driver) = 0;

  /**
   * @brief Trigger driver configuration.
   *
   */
  virtual void configureDriver() = 0;
  
  /**
   * @brief Get the object type (ActuatorType enum)
   *
   * @return ActuatorType actuator's type
   */
  virtual ActuatorType getType() = 0;
};
