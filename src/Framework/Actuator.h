#pragma once
#include "ActuatorDriver.h"
#include <string>
#include "HardwareLayer.h"
#include <memory>
// #include <list>

class Actuator
{

protected:
	static int nextID;
	const static std::string defaultName;
	int id;
	std::shared_ptr<IActuatorDriver> m_driver;

public:
	Actuator() = delete;
	std::string m_name;
	// std::list<Device*> deviceList;
	Actuator(std::shared_ptr<IActuatorDriver> driver);
	Actuator(std::shared_ptr<IActuatorDriver> driver, const std::string& name);
	void start();
	void stop();
	// Actuator(ActuatorDriverGPIO driver, std::string name, Device device);
	// addToDevice(Device device);
	// removeFromDevice(Device device);
	void setDriver(std::shared_ptr<IActuatorDriver> driver);
	~Actuator() = default;
};
