#pragma once
#include <memory>
#include <string>
#include "IActuator.h"

class IActuator;

/**
 * @interface IWaveform
 * @brief
 *
 */
class IWaveform {
 public:
  virtual void play(std::shared_ptr<IActuator> ac) = 0;
  virtual void init() = 0;
  virtual std::string patternToString() = 0;
};
