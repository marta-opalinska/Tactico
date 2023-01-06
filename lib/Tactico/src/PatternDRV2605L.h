/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <string>
#include <vector>

#include "DRV2605L_EFFECTS.h"
#include "HardwareLayer.h"

// average DRV2506L pattern time - not precise for some of the patterns!
#define AVERAGE_PATTERN_TIME 250
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
  int m_patternDuration;
  /**
   * @brief Construct a new DRV2605L Pattern
   *
   * @param patternIndex DRV2605L pattern index (based on DRV2605L_EFFECTS.h)
   * @param patternDuration there is an average pattern duration that will fit
   * most of the patterns but not every! In case it does not match the real
   * pattern duration please specify the time here.
   */
  explicit PatternDRV2605L(int patternIndex,
                           int patternDuration = AVERAGE_PATTERN_TIME);
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
   * @brief Get the time that takes to perform a pattern.
   *
   * @return int
   */
  int getPatternTime();
  /**
   * @brief Get the PatternType object
   *
   * @return PatternType
   */
  PatternType getType();
};
