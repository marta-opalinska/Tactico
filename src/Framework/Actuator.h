#pragma once
#include "ActuatorDriver.h"
#include <string>
#include "HardwareLayer.h"
// #include <list>

class Actuator
{

protected:
	static int nextID;
	const static std::string defaultName;
	int id;
	ActuatorDriver& m_driver;

public:
	Actuator() = delete;
	std::string m_name;
	// std::list<Device*> deviceList;
	Actuator(ActuatorDriver& m_driver);
	Actuator(ActuatorDriver& m_driver, const std::string& name);
	void start();
	void stop();
	// Actuator(ActuatorDriver driver, std::string name, Device device);
	// addToDevice(Device device);
	// removeFromDevice(Device device);
	void setDriver(ActuatorDriver& driver);
	~Actuator() = default;
};
