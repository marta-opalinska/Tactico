#include "PatternPWM.h"

PatternPWM::PatternPWM(std::vector<ModulationPWM> switching_modulation)
    : m_modulation_sequence(switching_modulation) {}

void PatternPWM::setModulation(std::vector<ModulationPWM> switching_modulation) {
  this->m_modulation_sequence = switching_modulation;
}

void PatternPWM::play(std::shared_ptr<IActuator> ac) {
  for (auto m : this->m_modulation_sequence) {
    // if()
    if (m.isOn) {
      ac->start();
    } else {
      ac->stop();
    }
    waitForMiliseconds(m.duration);
  }
}

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

// void Pattern::stop(std::shared_ptr<Actuator> ac)
// {
// }
// students[x]=y;
