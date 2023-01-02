/** Copyright 2022 <Marta Opalinska> **/

#pragma once

#include <Interfaces/IStep.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

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
