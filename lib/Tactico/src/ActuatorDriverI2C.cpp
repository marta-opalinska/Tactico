#pragma once
#include "ActuatorDriverI2C.h"

bool ActuatorDriverI2C::m_I2C_Initialised = true;

ActuatorDriverI2C::ActuatorDriverI2C(int address) : m_address(address) {
  this->init();
  this->m_usesGoPinFlag = false;
}

ActuatorDriverI2C::ActuatorDriverI2C(int address, int goPin)
    : m_address(address), m_goPin(goPin) {
  this->init();
  this->m_usesGoPinFlag = true;
}

void ActuatorDriverI2C::init() {
  if (!this->m_I2C_Initialised) {
    i2c_begin();
  }
}

// void ActuatorDriverI2C::setHighGPIO() {
//   setPinStatusTactico(this->m_GPIO_pin, 1);
// }

// void ActuatorDriverI2C::setLowGPIO() {
//   setPinStatusTactico(this->m_GPIO_pin, 0);
// }

// void ActuatorDriverI2C::play() {
//   this->setHighGPIO();
//   std::string s = "Actuator Driver START, GPIO ";
//   s.append(std::to_string(this->m_GPIO_pin));
//   s.append("\n");
//   printTactico(s);
// }

// void ActuatorDriverI2C::stop() {
//   this->setLowGPIO();
//   std::string s = "Actuator Driver STOP, GPIO ";
//   s.append(std::to_string(this->m_GPIO_pin));
//   s.append("\n");
//   printTactico(s);
// }
// void ActuatorDriverI2C::setPin(int new_GPIO) {
//   this->setLowGPIO();
//   this->m_GPIO_pin = new_GPIO;
//   this->init();
// }

// int ActuatorDriverI2C::getPin() {
//   return this->m_GPIO_pin;
// }

// void ActuatorDriverI2C::play(IWaveform pattern){

// }
