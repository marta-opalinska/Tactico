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

// void Pattern::stop(std::shared_ptr<Actuator> ac)
// {
// }
// students[x]=y;
