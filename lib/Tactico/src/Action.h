#pragma once
#include <Interfaces/IActuator.h>

#include <memory>
#include <vector>

#include "Step.h"

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
