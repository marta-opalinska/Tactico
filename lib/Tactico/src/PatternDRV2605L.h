/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <string>
#include <vector>
// clang-format off
#include "HardwareLayer.h"
// clang-format on

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
