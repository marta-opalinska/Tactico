#include "Actuator.h"
#include "Arduino.h"

int Actuator::nextID = 0;
std::string Actuator::defaultName = "actuator_";

Actuator::Actuator(ActuatorDriver& driver, std::string name)
	:m_driver(driver)
{
	this->id = ++nextID;
	this->name = name;
};

Actuator::Actuator(ActuatorDriver& driver)
	:m_driver(driver)
{
	this->id = ++nextID;
	this->name = defaultName;
	this->name.append(std::to_string(id));
};

void Actuator::start()
{
	Serial.print("Actuator ");
	Serial.print(this->name.c_str());
	Serial.print(": \n");
	this->m_driver.startActuator();
};

void Actuator::stop()
{
	Serial.print("Actuator ");
	Serial.print(this->name.c_str());
	Serial.print(": \n");
	this->m_driver.stopActuator();
};