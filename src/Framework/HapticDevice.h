#pragma once
#include "Actuator.h"
#include <string>
#include <vector>
#include <algorithm>

class HapticDevice
{
protected:
	static int nextID;
	static std::string defaultName;
	int id;
    std::vector<Actuator *> m_actuatorsList;

public:
    std::string m_name;
    HapticDevice() = default;
    ~HapticDevice() = default;
    HapticDevice(std::vector<Actuator *> actuatorsList, std::string name = "");
    HapticDevice(Actuator *singleActuator, std::string name = "");
    void renameDevice(std::string name);
    void addActuator(Actuator *actuator);
    void addActuators(std::vector<Actuator *> actuatorsVector);
    void removeActuator(Actuator *actuator);
    void removeActuator(int actuatorIndex);
    void removeActuator(std::string name);
    void swapActuator(Actuator *oldActuator, Actuator *newActuator);
    void startActuators();
    void stopActuators();
};