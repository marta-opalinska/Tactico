#pragma once
#include <memory>
#include <string>

#include "IActuator.h"

class IActuator;

/**
 * @interface IPattern
 * @brief
 *
 */

enum PatternType { ePWM, eDRV2505L};

class IPattern {
 protected:
  PatternType m_type;

 public:
  virtual void init() = 0;
  virtual std::string patternToString() = 0;
  virtual PatternType getType() = 0;
};
