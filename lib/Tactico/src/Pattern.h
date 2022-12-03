#pragma once
#include <Interfaces/IActuator.h>

#include <memory>
#include <vector>

#include "HardwareLayer.h"
#include "Tactico.h"

struct Modulation {
  int duration;
  bool isOn;
};

class IPattern {
 public:
  virtual void play(std::shared_ptr<IActuator> ac) = 0;
};

class PatternPWM : public IPattern {
 private:
  PatternPWM() = default;
  std::vector<Modulation> m_switching_modulation;

 public:
  // applyPattern(Actuator actuator)
  explicit PatternPWM(std::vector<Modulation> switching_modulation);
  void setModulation(std::vector<Modulation> switching_modulation);
  void play(std::shared_ptr<IActuator> ac);
  ~PatternPWM() = default;
};
