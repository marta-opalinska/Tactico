/** Copyright 2022 <Marta Opalinska> **/

#pragma once

#include <Interfaces/IStep.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

/**
 * @class WaitStep
 * @implements IStep
 * @brief Class that stores the wait time between steps in the Action.
 * @param m_waitTime value of the wait in miliseconds
 *
 */
class WaitStep : public IStep {
 protected:
  WaitStep() = default;

 public:
  /**
   * value of the wait in miliseconds
   *
   */
  unsigned int m_waitTime;
  /**
   * @brief Construct a new Wait Step object
   *
   * @param miliseconds
   */
  explicit WaitStep(unsigned int miliseconds);
  ~WaitStep() = default;

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
