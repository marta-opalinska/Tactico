#include "Actuator.h"
#include "Arduino.h"

int Actuator::nextID = 0;
std::string Actuator::defaultName = "actuator_";

Actuator::Actuator(ActuatorDriver& driver, std::string name)
	:m_driver(driver)
{
	this->id = ++nextID;
	this->m_name = name;
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
	this->m_driver.stopActuator();
};