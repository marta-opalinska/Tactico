#pragma once
#include <Interfaces/IActuator.h>

#include <memory>
#include <vector>

#include "HardwareLayer.h"
#include "Interfaces/IPattern.h"
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
 * @class PatternPWM
 * @brief
 * @param m_modulation_sequence vector or modulation sequence
 *
 */
class PatternPWM : public IPattern {
 private:
  PatternPWM() = default;
  std::vector<ModulationPWM> m_modulation_sequence;

 public:
  // applyPattern(Actuator actuator)
  explicit PatternPWM(std::vector<ModulationPWM> switching_modulation);
  void setModulation(std::vector<ModulationPWM> switching_modulation);
  void play(std::shared_ptr<IActuator> ac);
  ~PatternPWM() = default;
};
