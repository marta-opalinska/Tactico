/** Copyright 2022 <Marta Opalinska> **/

#include "WaitStep.h"

WaitStep::WaitStep(unsigned int miliseconds) : m_waitTime(miliseconds) {
  this->m_type = eWaitStep;
  this->m_needsPreconfigration = false;
}

void WaitStep::play() { waitFor(this->m_waitTime); }

void WaitStep::printStep() {
  std::string s = "STEP: ";
  s.append("Wait for : ");
  s.append(": ");
  s.append(std::to_string(this->m_waitTime));
  s.append("\n");
  printTactico(s);
}
StepType WaitStep::getType() { return this->m_type; }
