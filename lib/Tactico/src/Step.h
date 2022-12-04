#pragma once

#include <Interfaces/IActuator.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

/**
 * @interface IStep
 * @brief Interface for Action Step. Step is just one activity of the Actuator
 * or a wait/delay.
 *
 */
class IStep {
 public:
  virtual void play() = 0;
  virtual void printStep() = 0;
};

/**
 * @class SteoActuator
 * @implements IStep
 * @brief Class that store information and methods for an individual actuator
 * activation.
 * @param m_actuator actuator that the action is assigned to
 *
 */
class StepActuator : public IStep {
 protected:
  StepActuator() = default;

 public:
  // tep() = default;
  StepActuator(std::shared_ptr<IActuator> actuator, bool isStart);
  ~StepActuator() = default;
  std::shared_ptr<IActuator> m_actuator;
  bool m_isStart;
  void play();
  void printStep();
};

/**
 * @class StepWait
 * @implements IStep
 * @brief Class that stores the wait time between two steps in the Action.
 * @param m_waitTime value of the wait in miliseconds
 *
 */
class StepWait : public IStep {
 protected:
  StepWait() = default;

 public:
  // tep() = default;
  explicit StepWait(unsigned int miliseconds);
  ~StepWait() = default;
  unsigned int m_waitTime;
  void play();
  void printStep();
};
