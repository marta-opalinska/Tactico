/** Copyright 2022 <Marta Opalinska> **/

#pragma once

#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <memory>
#include <string>

#include "HardwareLayer.h"

/**
 * @brief Enum of the possible action step types. It is used for step specific
 * methods.
 *
 */
enum StepType { eActuatorStep, eWaitStep };

/**
 * @interface IStep
 * @brief Interface for Action Step. Step is just one activity of a given
 * Actuator or a wait/delay.
 *
 */
class IStep {
 protected:
  /**
   * step type based on enum StepType
   */
  StepType m_type;

 public:
  /**
   * defines if the actuator involved in the step needs to be preconfigured
   * before the action can be played e.g. by sending the pattern before hitting
   * GO
   */
  bool m_needsPreconfigration;
  /**
   * @brief Play the step.
   *
   */
  virtual void play() = 0;

  /**
   * @brief Print the step in the serial port (as String)
   *
   */
  virtual void printStep() = 0;

  /**
   * @brief Get the StepType of the object
   *
   * @return StepType
   */
  virtual StepType getType() = 0;
};
