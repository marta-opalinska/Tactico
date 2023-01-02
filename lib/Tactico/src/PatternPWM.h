/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <string>
#include <vector>

#include "HardwareLayer.h"
#include "Tactico.h"

/**
 * @brief Structure for PWM modulation
 * @details The structure consist of the duration of the pulse and if the signal
 * state (if is ON or OFF)
 * @param duration duration of the pulse
 * @param isOn flag defining if the state is ON or OFF
 *
 */
struct ModulationPWM {
  int duration;
  bool isOn;
};

/**
 * @class PatternPWM
 * @implements IPattern
 * @brief Class that stores the Pulse Width Mudulation pattern (effect) that can
 * be applied to the actuator that support this type of driver.
 */
class PatternPWM : public IPattern {
 private:
  PatternPWM() = default;

 public:
  /**
   * vector of modulation sequence
   */
  std::vector<ModulationPWM> m_modulation_sequence;
  /**
   * @brief Construct a new PWM pattern
   *
   * @param switching_modulation PWM switching modulation made from
   * ModulationPWM structure
   */
  explicit PatternPWM(std::vector<ModulationPWM> switching_modulation);
  ~PatternPWM() = default;

  /**
   * @brief Set the Modulation object
   *
   * @param switching_modulation
   */
  void setModulation(std::vector<ModulationPWM> switching_modulation);

  /**
   * @brief Initiate the pattern
   */
  void init();

  /**
   * @brief Pattern converted to string (helpful for serial output)
   *
   * @return std::string
   */
  std::string patternToString();

  /**
   * @brief Get the PatternType object
   *
   * @return PatternType
   */
  PatternType getType();
};
