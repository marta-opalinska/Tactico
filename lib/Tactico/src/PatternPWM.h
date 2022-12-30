/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuator.h>

#include <string>
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

 public:
  // applyPatternPWM(Actuator actuator)
  std::vector<ModulationPWM> m_modulation_sequence;
  explicit PatternPWM(std::vector<ModulationPWM> switching_modulation);
  void setModulation(std::vector<ModulationPWM> switching_modulation);
  // void play(std::shared_ptr<IActuator> ac);
  void init();
  std::string patternToString();
  PatternType getType();
  ~PatternPWM() = default;
};
