#include "Actuator.h"


int Actuator::nextID = 0;
const std::string Actuator::defaultName = "actuator_";

Actuator::Actuator(std::shared_ptr<IActuatorDriver> driver, const std::string& name)
	: m_driver(driver)
	, m_name(name)
{
	this->id = ++nextID;
};

Actuator::Actuator(std::shared_ptr<IActuatorDriver> driver)
	:m_driver(driver)
{
	this->id = ++nextID;
	this->m_name = defaultName;
	this->m_name.append(std::to_string(id));
};

void Actuator::start()
{
	std::string s = "Actuator ";
	s.append(this->m_name);
	s.append(": \n");
	printTactico(s);
	this->m_driver->startActuator();
};

void Actuator::stop()
{
	std::string s = "Actuator ";
	s.append(this->m_name);
	s.append(": \n");
	printTactico(s);
	this->m_driver->stopActuator();
};

void Actuator::setDriver(std::shared_ptr<IActuatorDriver> driver)
{
	this->m_driver = driver;
};