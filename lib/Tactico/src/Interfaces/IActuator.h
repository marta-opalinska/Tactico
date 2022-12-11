#pragma once
#include <Interfaces/IActuatorDriver.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

/**
 * @interface
 * @brief Interface for actuator - the interface is implemented by ActuatorERM
 * and ActuatorLRA classes
 */

class IActuator {
 protected:
  int id;
  std::shared_ptr<IActuatorDriver> m_driver;

  // const std::string defaultName;

 public:
  std::string m_name;
  IActuator(std::shared_ptr<IActuatorDriver> driver, const std::string &name)
      : m_driver(driver), m_name(name) {}
  explicit IActuator(std::shared_ptr<IActuatorDriver> driver) : m_driver(driver) {}

  virtual void start() = 0;
  virtual void stop() = 0;
  /**
   * @brief Assign Driver object to the actuator
   *
   * @param driver ActuatorDriver object to assign
   */
  virtual std::shared_ptr<IActuatorDriver> getDriver() = 0;
  virtual void setDriver(std::shared_ptr<IActuatorDriver> driver) = 0;
};
