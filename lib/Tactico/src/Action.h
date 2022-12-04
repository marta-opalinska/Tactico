#pragma once
#include <Interfaces/IActuator.h>

#include <memory>
#include <vector>

#include "Step.h"

/**
 * @class Action
 * @brief Class that can store multistep activity that can be performed on
 * multiple actuators
 * @details There are two typed of steps that an action can consist of :
 * StepWait (delay between two actions) and StepStepActuator (action that is
 * performed on a specific Actuator)
 * @param m_activitySteps vector of steps that belongs to the activity.
 */
class Action {
 private:
  std::vector<std::shared_ptr<IStep>> m_activitySteps;

 public:
  Action() = default;
  ~Action() = default;
  void addStep(std::shared_ptr<IActuator> actuator, bool isStart);
  void addStep(std::shared_ptr<IStep> step);
  void addWait(int miliseconds);
  void addWait(std::shared_ptr<StepWait> stepWait);
  // removes single step
  void removeStep(int stepPosition);
  std::vector<std::shared_ptr<IStep>> getSteps();
  void setSteps(std::vector<std::shared_ptr<IStep>> activitySteps);
  // if the same step was duplicated it will remove all the steps that are
  // associated with this pointer void removeStep(Step* step); replace single
  // step void replaceStepByID(Step* stepToReplace, Actuator *actuator, bool
  // isStart); if the same step was duplicated it will replace all the steps
  // that are associated with this pointer void replaceStep(int stepToReplaceID,
  // Actuator *actuator, bool isStart);
  void play();
};
