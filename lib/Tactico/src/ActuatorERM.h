#pragma once
#include <Interfaces/IActuator.h>

#include <memory>
#include <string>
#include <vector>

#include "Step.h"

#ifndef ACTUATOR_DEFAULT_NAME
#define ACTUATOR_DEFAULT_NAME "actuator_"
#endif

/**
 * @class ActuatorERM
 * @brief Class that stores information and methods for ERM actuator type. It
 * implements IActuator interface.
 * @implements IActuator
 * @param m_driver requirered parameter, links the actuator with the driver
 * @param m_name optional parameter, actuator custom name
 *
 */
class ActuatorERM : public IActuator {
 protected:
  static int nextID;
  // static const char defaultName[14];  // = "actuatorERM"
  static const std::string defaultName;  // = "actuatorERM"

 public:
  ActuatorERM() = delete;
  /**
   * @brief Construct a new ERM Actuator object
   *
   * @param driver required parameter, ActuatorDriver object to control the
   * physical interface
   */
  explicit ActuatorERM(std::shared_ptr<IActuatorDriver> driver);
  /**
   * @brief Construct a new ERM Actuator object with a custom name
   *
   * @param driver required parameter, ActuatorDriver object to control the
   * physical interface
   * @param name custom Actuator name
   */
  ActuatorERM(std::shared_ptr<IActuatorDriver> driver, const std::string &name);
  void play();
  void stop();
  /**
   * @brief Assign Driver object to the actuator
   *
   * @param driver ActuatorDriver object to assign
   */
  void setDriver(std::shared_ptr<IActuatorDriver> driver);
  std::shared_ptr<IActuatorDriver> getDriver();
  ~ActuatorERM() = default;
};
