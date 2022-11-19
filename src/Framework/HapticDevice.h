#pragma once
#include "Actuator.h"
#include <string>
#include <vector>
#include <algorithm> 

class HapticDevice
{
private:
    std::vector<Actuator*> m_actuatorsList;
public:
    HapticDevice() = default;
    ~HapticDevice() = default;
    HapticDevice(std::vector<Actuator*> actuatorsList);
    HapticDevice(Actuator* singleActuator);
    void addActuator(Actuator* actuator);
    void removeActuator(Actuator* actuator);
    void removeActuator(int actuatorIndex);
    void removeActuator(std::string name);
    void startActuators();
    void stopActuators();
};