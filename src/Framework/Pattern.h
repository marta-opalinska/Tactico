#pragma once
#include "Actuator.h"
#include <vector>
#include <memory>
#include "Tactico.h"
#include "HardwareLayer.h"


struct Modulation {
    int duration;
    bool isOn;
};

class Pattern
{
private:
    Pattern() = default;
    std::vector<Modulation> m_switching_modulation;
public:
    // applyPattern(Actuator actuator)
    Pattern(std::vector<Modulation> switching_modulation);
    void setModulation(std::vector<Modulation> switching_modulation);
    void play(std::shared_ptr<Actuator> ac);
    void stop(std::shared_ptr<Actuator> ac);
    ~Pattern() = default;
};