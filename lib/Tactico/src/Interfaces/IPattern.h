/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <memory>
#include <string>

#include "IActuator.h"

class IActuator;

/**
 * @brief Enum of the possible pattern types. It is used for pattern specific
 * methods.
 *
 */
enum PatternType { ePWM, eDRV2505L };

/**
 * @interface IPattern
 * @brief An interface for actuator's pattern. The intefrace is implemented by PatternPWM and PatternDRV2605L classes. 
 *
 */
class IPattern {
 protected:
  /**
   * pattern type based on enum PatternType
   */
  PatternType m_type;

 public:
  /**
   * @brief Initiate the pattern
   */
  virtual void init() = 0;

  /**
   * @brief Pattern converted to string (helpful for serial output)
   *
   * @return std::string saved pattern as a string
   */
  virtual std::string patternToString() = 0;

  /**
   * @brief Get the PatternType of the object
   *
   * @return PatternType
   */
  virtual PatternType getType() = 0;
};
