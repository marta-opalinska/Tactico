#include "Step.h"

StepActuator::StepActuator(std::shared_ptr<IActuator> actuator, bool isStart)
    : m_actuator(actuator), m_isStart(isStart) {}

void StepActuator::play() {
  if (this->m_isStart) {
    this->m_actuator->start();
  } else {
    this->m_actuator->stop();
  }
}

void StepActuator::printStep() {
  std::string s = "STEP: ";
  s.append(this->m_actuator->m_name);
  s.append(": ");
  s.append(this->m_isStart ? "Start" : "Stop");
  s.append("\n");
  printTactico(s);
}

StepWait::StepWait(unsigned int miliseconds) : m_waitTime(miliseconds) {}

void StepWait::play() { waitForMiliseconds(this->m_waitTime); }

void StepWait::printStep() {
  std::string s = "STEP: ";
  s.append("Wait for : ");
  s.append(": ");
  s.append(std::to_string(this->m_waitTime));
  s.append("\n");
  printTactico(s);
}
