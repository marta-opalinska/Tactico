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
class IPattern {
 public:
  virtual void play(std::shared_ptr<IActuator> ac) = 0;
  virtual std::string patternToString() = 0;
};
