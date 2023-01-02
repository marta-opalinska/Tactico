/** Copyright 2022 <Marta Opalinska> **/

#include "WaitStep.h"

WaitStepImpl::WaitStepImpl(unsigned int miliseconds) : m_waitTime(miliseconds) {
  this->m_type = eWaitStep;
  this->m_needsPreconfigration = false;
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
