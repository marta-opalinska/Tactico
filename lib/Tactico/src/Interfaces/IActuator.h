#pragma once
#include <Interfaces/IActuatorDriver.h>
#include <string>
#include "HardwareLayer.h"
#include <memory>
// #include <list>

class IActuator
{

protected:
	// static int nextID;
	// const static std::string defaultName;
	int id;
	std::shared_ptr<IActuatorDriver> m_driver;

public:
	std::string m_name;
	// ActuatorERM(std::shared_ptr<IActuatorDriver> driver);
	// ActuatorERM(std::shared_ptr<IActuatorDriver> driver, const std::string& name);
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void setDriver(std::shared_ptr<IActuatorDriver> driver) = 0;
};
