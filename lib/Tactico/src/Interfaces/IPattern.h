#pragma once
#include "IActuator.h"
#include <memory>

/**
 * @interface IPattern
 * @brief 
 * 
 */
class IPattern {
 public:
  virtual void play(std::shared_ptr<IActuator> ac) = 0;
};