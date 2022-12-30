/** Copyright 2022 <Marta Opalinska> **/

#pragma once

#include <Interfaces/IActuator.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"
#include "Interfaces/IPattern.h"

enum StepType { eActuator, eWait };

/**
 * @interface IStep
 * @brief Interface for Action Step. Step is just one activity of the Actuator
 * or a wait/delay.
 *
 */
class IStep {
 protected:
  StepType m_type;
 public:
  virtual void play() = 0;
  virtual void printStep() = 0;
  virtual StepType getType() = 0;
};

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

/**
 * @class WaitStepImpl
 * @implements IStep
 * @brief Class that stores the wait time between two steps in the Action.
 * @param m_waitTime value of the wait in miliseconds
 *
 */
class WaitStepImpl : public IStep {
 protected:
  WaitStepImpl() = default;

 public:
  // tep() = default;
  explicit WaitStepImpl(unsigned int miliseconds);
  ~WaitStepImpl() = default;
  unsigned int m_waitTime;
  void play();
  void printStep();
  StepType getType();
};
