#include "Actuator.h"
#include "Arduino.h"

int Actuator::nextID = 0;
const std::string Actuator::defaultName = "actuator_";

Actuator::Actuator(ActuatorDriver& driver, const std::string& name)
	: m_driver(driver)
	, m_name(name)
{
	this->id = ++nextID;
};

Actuator::Actuator(ActuatorDriver& driver)
	:m_driver(driver)
{
	this->id = ++nextID;
	this->m_name = defaultName;
	this->m_name.append(std::to_string(id));
};

void Actuator::start()
{
	Serial.print("Actuator ");
	Serial.print(this->m_name.c_str());
	Serial.print(": \n");
	this->m_driver.startActuator();
};

void Actuator::stop()
{
	Serial.print("Actuator ");
	Serial.print(this->m_name.c_str());
	Serial.print(": \n");
	this->m_driver.startActuator();
};