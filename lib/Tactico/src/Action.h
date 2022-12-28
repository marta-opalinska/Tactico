#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <memory>
#include <vector>
#include <string>

#include "Step.h"

// the limit of DRV2605L driver when it comes to the steps saving
#define MAX_STEPS 5

/**
 * @class Action
 * @brief Class that can store multistep activity that can be performed on
 * multiple actuators
 * @details There are two typed of steps that an action can consist of :
 * WaitStepImpl (delay between two actions) and StepStepActuator (action that is
 * performed on a specific Actuator)
 * @param m_activitySteps vector of steps that belongs to the activity.
 * @param m_actuators list of all the actuators that are in the action
 */
class Action {
 private:
  std::vector<std::shared_ptr<IStep>> m_activitySteps;
  std::vector<std::shared_ptr<IActuator>> m_actuators;
  int m_nextStepID;

 public:
  explicit Action();
  ~Action() = default;
  void addStep(std::shared_ptr<IActuator> actuator, std::shared_ptr<IPattern> pattern);
  void addStep(std::shared_ptr<IStep> step);
  void addWait(int miliseconds);
  void addWait(std::shared_ptr<WaitStepImpl> stepWait);
  std::vector<std::shared_ptr<IStep>> getSteps();
  void setSteps(std::vector<std::shared_ptr<IStep>> activitySteps);
  void setAction();
  void clear();
  // if the same step was duplicated it will remove all the steps that are
  // associated with this pointer void removeStep(Step* step); replace single
  // step void replaceStepByID(Step* stepToReplace, Actuator *actuator, bool
  // isStart); if the same step was duplicated it will replace all the steps
  // that are associated with this pointer void replaceStep(int stepToReplaceID,
  // Actuator *actuator, bool isStart);
  void play();
  void setAndPlay();
};
