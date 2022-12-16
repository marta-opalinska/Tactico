#pragma once
#include "ActuatorDriverGPIO.h"

ActuatorDriverGPIO::ActuatorDriverGPIO(int GPIO_pin) : m_GPIO_pin(GPIO_pin) {
  this->init();
}

void ActuatorDriverGPIO::init() {
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

void ActuatorDriverGPIO::play() {
  this->setHighGPIO();
  std::string s = "Actuator Driver START, GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append("\n");
  printTactico(s);
}

void ActuatorDriverGPIO::stop() {
  this->setLowGPIO();
  std::string s = "Actuator Driver STOP, GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append("\n");
  printTactico(s);
}
void ActuatorDriverGPIO::setPin(int new_GPIO) {
  this->setLowGPIO();
  this->m_GPIO_pin = new_GPIO;
  this->init();
}

int ActuatorDriverGPIO::getPin() {
  return this->m_GPIO_pin;
}

// void ActuatorDriverGPIO::play(IWaveform pattern){

// }

