/** Copyright 2022 <Marta Opalinska> **/

#include "ActuatorStep.h"

ActuatorStep::ActuatorStep(std::shared_ptr<IActuator> actuator,
                                   std::shared_ptr<IPattern> pattern)
    : m_actuator(actuator), m_pattern(pattern) {
  this->m_type = eActuatorStep;
  this->m_needsPreconfigration =
      this->m_actuator->getDriver()->m_needsPreconfigration;
}

void ActuatorStep::play() { this->m_actuator->play(this->m_pattern); }

void ActuatorStep::printStep() {
  std::string s = "STEP: ";
  s.append(this->m_actuator->m_name);
  s.append(": ");
  s.append(this->m_pattern->patternToString());
  s.append("\n");
  printTactico(s);
}

StepType ActuatorStep::getType() { return this->m_type; }
