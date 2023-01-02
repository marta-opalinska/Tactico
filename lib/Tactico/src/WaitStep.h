/** Copyright 2022 <Marta Opalinska> **/

#pragma once

#include <Interfaces/IStep.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

/**
 * @class WaitStep
 * @implements IStep
 * @brief Class that stores the wait time between two steps in the Action.
 * @param m_waitTime value of the wait in miliseconds
 *
 */
class WaitStep : public IStep {
 protected:
  WaitStep() = default;

 public:
  // tep() = default;
  explicit WaitStep(unsigned int miliseconds);
  ~WaitStep() = default;
  unsigned int m_waitTime;
  void play();
  void printStep();
  StepType getType();
};
