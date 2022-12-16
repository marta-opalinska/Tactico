#include "WaveformPWM.h"

WaveformPWM::WaveformPWM(std::vector<ModulationPWM> switching_modulation)
    : m_modulation_sequence(switching_modulation) {
}

void WaveformPWM::init() {}

void WaveformPWM::setModulation(
    std::vector<ModulationPWM> switching_modulation) {
  this->m_modulation_sequence = switching_modulation;
}

void WaveformPWM::play(std::shared_ptr<IActuator> ac) {
  for (auto m : this->m_modulation_sequence) {
    // if()
    if (m.isOn) {
      ac->play();
    } else {
      ac->stop();
    }
    waitFor(m.duration);
  }
}

std::string WaveformPWM::patternToString() {
  std::string s = "";
  for (auto m : this->m_modulation_sequence) {
    s.append(std::to_string(m.isOn));
    s.append(" ");
    s.append(std::to_string(m.duration));
    s.append(", ");
  }
  return s;
}

// void WaveformPWM::stop(std::shared_ptr<Actuator> ac)
// {
// }
// students[x]=y;
