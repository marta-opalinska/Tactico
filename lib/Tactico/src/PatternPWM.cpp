/** Copyright 2022 <Marta Opalinska> **/

#include "PatternPWM.h"

PatternPWM::PatternPWM(std::vector<ModulationPWM> switching_modulation)
    : m_modulation_sequence(switching_modulation) {
  this->m_type = ePWM;
}

void PatternPWM::init() {}

void PatternPWM::setModulation(
    std::vector<ModulationPWM> switching_modulation) {
  this->m_modulation_sequence = switching_modulation;
}

// void PatternPWM::play(std::shared_ptr<IActuator> ac) {
//   for (auto m : this->m_modulation_sequence) {
//     // if()
//     if (m.isOn) {
//       ac->play();
//     } else {
//       ac->stop();
//     }
//     waitFor(m.duration);
//   }
// }

std::string PatternPWM::patternToString() {
  std::string s = "";
  for (auto m : this->m_modulation_sequence) {
    s.append(std::to_string(m.isOn));
    s.append(" ");
    s.append(std::to_string(m.duration));
    s.append(", ");
  }
  return s;
}

int PatternPWM::getPatternDuration() {
  int total_time = 0;
  for (auto modulation : this->m_modulation_sequence) {
    total_time += modulation.duration;
  }
  return total_time;
}

PatternType PatternPWM::getType() { return this->m_type; }

// void PatternPWM::stop(std::shared_ptr<Actuator> ac)
// {
// }
// students[x]=y;
