#include "Step.h"

ActuatorStepImpl::ActuatorStepImpl(std::shared_ptr<IActuator> actuator,
                           std::shared_ptr<IWaveform> pattern)
    : m_actuator(actuator), m_waveform(pattern) {}

void ActuatorStepImpl::play() {
  this->m_waveform->play(this->m_actuator);
}

void ActuatorStepImpl::printStep() {
  std::string s = "STEP: ";
  s.append(this->m_actuator->m_name);
  s.append(": ");
  s.append(this->m_waveform->patternToString());
  s.append("\n");
  printTactico(s);
}

WaitStepImpl::WaitStepImpl(unsigned int miliseconds) : m_waitTime(miliseconds) {}

void WaitStepImpl::play() { waitFor(this->m_waitTime); }

void WaitStepImpl::printStep() {
  std::string s = "STEP: ";
  s.append("Wait for : ");
  s.append(": ");
  s.append(std::to_string(this->m_waitTime));
  s.append("\n");
  printTactico(s);
}
