/** Copyright 2022 <Marta Opalinska> **/

#include "Step.h"

ActuatorStepImpl::ActuatorStepImpl(std::shared_ptr<IActuator> actuator,
                                   std::shared_ptr<IPattern> pattern)
    : m_actuator(actuator), m_pattern(pattern) {
  this->m_type = eActuatorStep;
}

void ActuatorStepImpl::play() { this->m_actuator->play(this->m_pattern); }

void ActuatorStepImpl::printStep() {
  std::string s = "STEP: ";
  s.append(this->m_actuator->m_name);
  s.append(": ");
  s.append(this->m_pattern->patternToString());
  s.append("\n");
  printTactico(s);
}

StepType ActuatorStepImpl::getType() { return this->m_type; }

WaitStepImpl::WaitStepImpl(unsigned int miliseconds) : m_waitTime(miliseconds) {
  this->m_type = eWaitStep;
}

void WaitStepImpl::play() { waitFor(this->m_waitTime); }

void WaitStepImpl::printStep() {
  std::string s = "STEP: ";
  s.append("Wait for : ");
  s.append(": ");
  s.append(std::to_string(this->m_waitTime));
  s.append("\n");
  printTactico(s);
}
StepType WaitStepImpl::getType() { return this->m_type; }
