#include "Action.h"

Action::Action() { this->m_nextStepID = 0; }

void Action::addStep(std::shared_ptr<IActuator> actuator,
                     std::shared_ptr<IPattern> pattern) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  this->m_activitySteps.push_back(
      std::make_shared<ActuatorStepImpl>(actuator, pattern));
  this->m_nextStepID++;
}

void Action::addStep(std::shared_ptr<IStep> step) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  this->m_activitySteps.push_back(step);
  this->m_nextStepID++;
}

void Action::addWait(int miliseconds) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  this->m_activitySteps.push_back(std::make_shared<WaitStepImpl>(miliseconds));
  this->m_nextStepID++;
}

void Action::addWait(std::shared_ptr<WaitStepImpl> stepWait) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  this->m_activitySteps.push_back(stepWait);
  this->m_nextStepID++;
}

void Action::clear() {
  this->m_nextStepID = 0;
  this->m_activitySteps.clear();
  this->m_actuators.clear();
}

std::vector<std::shared_ptr<IStep>> Action::getSteps() {
  return this->m_activitySteps;
}

void Action::setSteps(std::vector<std::shared_ptr<IStep>> activitySteps) {
  this->m_activitySteps = activitySteps;
}

// TODO add steps to all the actuators in the action
void Action::setAction() {}
void Action::play() {
  for (auto step : this->m_activitySteps) {
    step->printStep();
    step->play();
  }
}

void Action::setAndPlay() {
  this->setAction();
  this->play();
}
