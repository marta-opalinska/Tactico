/** Copyright 2022 <Marta Opalinska> **/

#pragma once

#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>
#include <Interfaces/IStep.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

/**
 * @class ActuatorStep
 * @implements IStep
 * @brief Class that store information and methods for an individual actuator
 * activation.
 *
 */
class ActuatorStep : public IStep {
 protected:
  ActuatorStep() = default;

 public:
  /**
   * @brief actuator that the step is assigned to
   *
   */
  std::shared_ptr<IActuator> m_actuator;
  /**
   * @brief pattern that the step will perform
   *
   */
  std::shared_ptr<IPattern> m_pattern;
  /**
   * @brief Construct a new Actuator Step object
   *
   * @param actuator actuator that the step is assigned to
   * @param pattern pattern that the step will perform
   */
  ActuatorStep(std::shared_ptr<IActuator> actuator,
               std::shared_ptr<IPattern> pattern);
  ~ActuatorStep() = default;

  /**
   * @brief Print the step in the serial port (as String)
   *
   */
  void printStep();

  /**
   * @brief Get the StepType of the object
   *
   * @return StepType
   */
  StepType getType();
};
