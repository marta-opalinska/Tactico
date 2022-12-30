#pragma once
#include <Interfaces/IPattern.h>

#include <memory>

#include "HardwareLayer.h"

class IController {
 public:
  virtual void connect() = 0;
  virtual void sendConfiguration() = 0;
  virtual void onCommand() = 0;
};
