#pragma once
#include <Interfaces/IActuator.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Interfaces/IPattern.h"
#include "PatternPWM.h"
#include "Step.h"

#ifndef ACTUATOR_ERM_DEFAULT_NAME
#define ACTUATOR_ERM_DEFAULT_NAME "actuatorERM_"
#endif

class PatternPWM;

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
  // void play();
  // void play(std::shared_ptr<IPattern> pattern);

  bool play(std::shared_ptr<IPattern> pattern);
  // void playDRV2505L(std::shared_ptr<PatternPWM> patternPWM);
  // void stop();
  /**
   * @brief Assign Driver object to the actuator
   *
   * @param driver ActuatorDriver object to assign
   */
  void setDriver(std::shared_ptr<IActuatorDriver> driver);
  std::shared_ptr<IActuatorDriver> getDriver();
  ActuatorType getType();
  ~ActuatorERM() = default;
};
