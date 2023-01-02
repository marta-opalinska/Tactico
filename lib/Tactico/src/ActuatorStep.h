/** Copyright 2022 <Marta Opalinska> **/

#pragma once

#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>
#include <Interfaces/IStep.h>

#include <memory>
#include <string>
// clang-format off
#include "HardwareLayer.h"
// clang-format on

/**
 * @class ActuatorStep
 * @implements IStep
 * @brief Class that store information and methods for an individual actuator
 * activation.
 * @param m_actuator actuator that the action is assigned to
 *
 */
class ActuatorStepImpl : public IStep {
 protected:
  ActuatorStepImpl() = default;

 public:
  // tep() = default;
  ActuatorStepImpl(std::shared_ptr<IActuator> actuator,
                   std::shared_ptr<IPattern> pattern);
  ~ActuatorStepImpl() = default;
  std::shared_ptr<IActuator> m_actuator;
  std::shared_ptr<IPattern> m_pattern;
  void play();
  void printStep();
  StepType getType();
};
