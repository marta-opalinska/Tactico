#pragma once
#include "ActuatorDriver.h"
#include <string>
// #include <list>

class Actuator
{

protected:
	static int nextID;
	static std::string defaultName;
	int id;

public:
	Actuator() = delete;
	std::string name;
	ActuatorDriver m_driver;
	//std::list<Device*> deviceList;
	Actuator(ActuatorDriver& m_driver);
	Actuator(ActuatorDriver& m_driver, std::string name);
	void start();
	void stop();
	//Actuator(ActuatorDriver driver, std::string name, Device device);
	//addToDevice(Device device);
	//removeFromDevice(Device device);
	~Actuator() = default;
};

