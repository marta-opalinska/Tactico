#pragma once
#include "ActuatorDriverGPIO.h"

ActuatorDriverGPIO::ActuatorDriverGPIO(int GPIO_pin) : m_GPIO_pin(GPIO_pin) {
  this->initDriver();
}

void ActuatorDriverGPIO::initDriver() {
  setPinModeTactico(this->m_GPIO_pin, OUTPUT);
  std::string s = "Set GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append(" as OUTPUT.\n");
  printTactico(s);
}

void ActuatorDriverGPIO::setHighGPIO() {
  setPinStatusTactico(this->m_GPIO_pin, 1);
}

void ActuatorDriverGPIO::setLowGPIO() {
  setPinStatusTactico(this->m_GPIO_pin, 0);
}

void ActuatorDriverGPIO::startActuator() {
  this->setHighGPIO();
  std::string s = "Actuator Driver START, GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append("\n");
  printTactico(s);
}

void ActuatorDriverGPIO::stopActuator() {
  this->setLowGPIO();
  std::string s = "Actuator Driver STOP, GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append("\n");
  printTactico(s);
}
void ActuatorDriverGPIO::setDriverPin(int new_GPIO) {
  this->setLowGPIO();
  this->m_GPIO_pin = new_GPIO;
  this->initDriver();
}

int ActuatorDriverGPIO::getDriverPin() {
  return this->m_GPIO_pin;
}

// void ActuatorDriverGPIO::play(IPattern pattern){

// }

