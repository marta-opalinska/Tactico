#pragma once
#include "ActuatorDriverGPIO.h"

ActuatorDriverGPIO::ActuatorDriverGPIO(int GPIO_pin)
	: m_GPIO_pin(GPIO_pin)
{
	this->initDriver();
};

void ActuatorDriverGPIO::initDriver()
{
	pinMode(this->m_GPIO_pin, OUTPUT);
	Serial.print("Set GPIO ");
	Serial.print(this->m_GPIO_pin);
	Serial.print(" as OUTPUT.\n");
};

void ActuatorDriverGPIO::setHighGPIO()
{
	digitalWrite(this->m_GPIO_pin, HIGH);
};

void ActuatorDriverGPIO::setLowGPIO()
{
	digitalWrite(this->m_GPIO_pin, LOW);
};

void ActuatorDriverGPIO::startActuator()
{
	this->setHighGPIO();
	std::string s = "Actuator Driver START, GPIO ";
	s.append(std::to_string(this->m_GPIO_pin));
	s.append("\n");
	printTactico(s);
};

void ActuatorDriverGPIO::stopActuator()
{
	this->setLowGPIO();
	std::string s = "Actuator Driver STOP, GPIO ";
	s.append(std::to_string(this->m_GPIO_pin));
	s.append("\n");
	printTactico(s);
}
void ActuatorDriverGPIO::editDriver(int new_GPIO)
{
	this->setLowGPIO();
	this->m_GPIO_pin = new_GPIO;
	this->initDriver();
};

// void ActuatorDriverGPIO::play(int time)
//{
// }
