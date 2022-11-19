#pragma once
#include "Actuator.h"
#include <string>

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
	this->m_driver.startActuator();
};

void Actuator::stop()
{
	this->m_driver.stopActuator();
};