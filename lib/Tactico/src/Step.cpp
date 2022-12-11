#include "Step.h"

StepActuator::StepActuator(std::shared_ptr<IActuator> actuator,
                           std::shared_ptr<IPattern> pattern)
    : m_actuator(actuator), m_pattern(pattern) {}

void StepActuator::play() {
  this->m_pattern->play(this->m_actuator);
}

void StepActuator::printStep() {
  std::string s = "STEP: ";
  s.append(this->m_actuator->m_name);
  s.append(": ");
  s.append(this->m_pattern->patternToString());
  s.append("\n");
  printTactico(s);
}

StepWait::StepWait(unsigned int miliseconds) : m_waitTime(miliseconds) {}

void StepWait::play() { waitFor(this->m_waitTime); }

void StepWait::printStep() {
  std::string s = "STEP: ";
  s.append("Wait for : ");
  s.append(": ");
  s.append(std::to_string(this->m_waitTime));
  s.append("\n");
  printTactico(s);
}
