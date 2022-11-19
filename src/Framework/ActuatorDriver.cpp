#pragma once
#include "ActuatorDriver.h"

ActuatorDriver::ActuatorDriver(int GPIO_pin)
{
	this->GPIO_pin = GPIO_pin;
};

void ActuatorDriver::initGPIO(int gpio)
{

};

void ActuatorDriver::setHighGPIO(int gpio)
{
};

void ActuatorDriver::setLowGPIO(int gpio)
{
};

void ActuatorDriver::startActuator()
{

};

void ActuatorDriver::stopActuator()
{
};

//void ActuatorDriver::play(int time)
//{
//}
