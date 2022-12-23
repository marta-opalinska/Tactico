#pragma once
#include <Interfaces/IActuator.h>

#include <vector>

#include "HardwareLayer.h"
#include "Interfaces/IPattern.h"
#include "Tactico.h"

/**
 * @class PatternDRV2605L
 * @brief
 * @param m_modulation_sequence vector or modulation sequence
 *
 */

class PatternDRV2605L : public IPattern {
 private:
  PatternDRV2605L() = default;

 public:
  int m_patternIndex;
  explicit PatternDRV2605L(int patternIndex);
  // void play(std::shared_ptr<IActuator> ac);
  // void init(int driverID);
  void init();
  std::string patternToString();
  PatternType getType();
  ~PatternDRV2605L() = default;
};
