#include "Action.h"

#include "string"

void Action::addStep(std::shared_ptr<IActuator> actuator, std::shared_ptr<IWaveform> pattern) {
  this->m_activitySteps.push_back(
      std::make_shared<ActuatorStepImpl>(actuator, pattern));
}

void Action::addStep(std::shared_ptr<IStep> step) {
  this->m_activitySteps.push_back(step);
}

void Action::addWait(int miliseconds) {
  this->m_activitySteps.push_back(std::make_shared<WaitStepImpl>(miliseconds));
}

void Action::addWait(std::shared_ptr<WaitStepImpl> stepWait) {
  this->m_activitySteps.push_back(stepWait);
}

void Action::removeStep(int stepPosition) {
  this->m_activitySteps.erase(this->m_activitySteps.begin() + stepPosition);
}

// void Activity::removeStep(Step* step)
// {
// }

// void Activity::replaceStepByID(Step* stepToReplace, Actuator* actuator, bool
// isStart)
// {
// }

// void Activity::replaceStep(int stepToReplaceID, Actuator* actuator, bool
// isStart)
// {
// }
std::vector<std::shared_ptr<IStep>> Action::getSteps() {
  return this->m_activitySteps;
}

void Action::setSteps(std::vector<std::shared_ptr<IStep>> activitySteps) {
  this->m_activitySteps = activitySteps;
}

void Action::play() {
  for (auto step : this->m_activitySteps) {
    step->printStep();
    step->play();
  }
}
