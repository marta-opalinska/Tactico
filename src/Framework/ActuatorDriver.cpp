#pragma once
#include "ActuatorDriver.h"
#include "Arduino.h"

ActuatorDriver::ActuatorDriver(int GPIO_pin)
{
	this->GPIO_pin = GPIO_pin;
	this->initGPIO();
};

void ActuatorDriver::initGPIO()
{
	pinMode(this->GPIO_pin, OUTPUT);
	Serial.print("Set GPIO ");
	Serial.print(this->GPIO_pin);
	Serial.print(" as OUTPUT.\n");
};

void ActuatorDriver::setHighGPIO()
{
	digitalWrite(this->GPIO_pin, HIGH);
};

void ActuatorDriver::setLowGPIO()
{
	digitalWrite(this->GPIO_pin, LOW);
};

void ActuatorDriver::startActuator()
{
	this->setHighGPIO();
	Serial.print("Actuator START, GPIO ");
	Serial.print(this->GPIO_pin);
	Serial.print("\n");
};

void ActuatorDriver::stopActuator()
{
	this->setLowGPIO();
	Serial.print("Actuator STOP, GPIO ");
	Serial.print(this->GPIO_pin);
	Serial.print("\n");
}
void ActuatorDriver::editGPIO(int new_GPIO)
{
	this->setLowGPIO();
	this->GPIO_pin = new_GPIO;
	this->initGPIO();
};

// void ActuatorDriver::play(int time)
//{
// }
