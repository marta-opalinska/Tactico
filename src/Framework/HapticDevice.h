#pragma once
#include "Actuator.h"
#include <string>
#include <vector>
#include <algorithm>

class HapticDevice
{
protected:
	static int nextID;
	const static std::string defaultName;
	int id;
    std::vector<Actuator *> m_actuatorsList;

public:
    std::string m_name;
    HapticDevice() = default;
    ~HapticDevice() = default;
    HapticDevice(std::vector<Actuator *> actuatorsList, const std::string & name = "");
    HapticDevice(Actuator *singleActuator, const std::string & name = "");
    void renameDevice(const std::string & name);
    void addActuator(Actuator *actuator);
    void addActuators(std::vector<Actuator *> actuatorsVector);
    void removeActuator(Actuator *actuator);
    void removeActuator(int actuatorPosition);
    void removeActuator(const std::string & name);
    // void swapActuator(Actuator* oldActuator, Actuator* newActuator);
    void startActuators();
    void stopActuators();
};