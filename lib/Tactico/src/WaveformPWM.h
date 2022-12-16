#pragma once
#include <Interfaces/IActuator.h>

#include <vector>

#include "HardwareLayer.h"
#include "Interfaces/IWaveform.h"
#include "Tactico.h"

/**
 * @brief Structure for PWM modulation
 * @details The structure consist of the duration of the pulse and if the signal
 * state (if is ON or OFF)
 *
 */
struct ModulationPWM {
  int duration;
  bool isOn;
};

/**
 * @class WaveformPWM
 * @brief
 * @param m_modulation_sequence vector or modulation sequence
 *
 */
class WaveformPWM : public IWaveform {
 private:
  WaveformPWM() = default;
  std::vector<ModulationPWM> m_modulation_sequence;

 public:
  // applyWaveformPWM(Actuator actuator)
  explicit WaveformPWM(std::vector<ModulationPWM> switching_modulation);
  void setModulation(std::vector<ModulationPWM> switching_modulation);
  void play(std::shared_ptr<IActuator> ac);
  void init();
  std::string patternToString();
  ~WaveformPWM() = default;
};
