#pragma once
#include <Interfaces/IActuator.h>
#include "Action.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

class HapticDevice
{
protected:
	static int nextID;
	const static std::string defaultName;
	int id;
    std::vector<std::shared_ptr<IActuator>> m_actuatorsList;
    std::map<std::string, std::shared_ptr<Action>> deviceActions;

public:
    std::string m_name;
    HapticDevice() = default;
    ~HapticDevice() = default;
    HapticDevice(std::vector<std::shared_ptr<IActuator>> actuatorsList, const std::string & name = "");
    HapticDevice(std::shared_ptr<IActuator> singleActuator, const std::string & name = "");
    void renameDevice(const std::string & name);
    void addActuator(std::shared_ptr<IActuator> actuator);
    void addActuators(std::vector<std::shared_ptr<IActuator>> actuatorsVector);
    void removeActuator(std::shared_ptr<IActuator> actuator);
    void removeActuator(int actuatorPosition);
    void removeActuator(const std::string & name);
    void 
    // void swapActuator(Actuator* oldActuator, Actuator* newActuator);
    void startActuators();
    void stopActuators();
};