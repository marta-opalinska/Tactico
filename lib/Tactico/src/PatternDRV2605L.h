/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <string>
#include <vector>

#include "DRV2605L_EFFECTS.h"
#include "HardwareLayer.h"

/**
 * @class PatternDRV2605L
 * @implements IPattern
 * @brief Class that stores the DRV2605L effect pattern that can be applied to
 * LRA or ERM actuator controlled to DRV2605L driver.
 * @see DRV2605L_EFFECTS.h header with haptic effects for the Pattern
 */
class PatternDRV2605L : public IPattern {
 private:
  PatternDRV2605L() = default;

 public:
  /**
   * DRV2605L pattern index (based on DRV2605L_EFFECTS.h)
   */
  int m_patternIndex;
  /**
   * @brief Construct a new DRV2605L Pattern
   *
   * @param patternIndex DRV2605L pattern index (based on DRV2605L_EFFECTS.h)
   */
  explicit PatternDRV2605L(int patternIndex);
  ~PatternDRV2605L() = default;

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
