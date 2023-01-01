/** Copyright 2022 <Marta Opalinska> **/

#include "ActuatorDriverI2C.h"

bool ActuatorDriverI2C::m_I2C_Initialised = false;

ActuatorDriverI2C::ActuatorDriverI2C() { this->initI2CBus(); }

void ActuatorDriverI2C::initI2CBus() {
  if (!this->m_I2C_Initialised) {
    i2c_begin();
    m_I2C_Initialised = true;
  }
  this->m_type = eI2C;
}
void ActuatorDriverI2C::init() {
  this->initI2CBus();
  this->m_needsPreconfigration = false;
}

int ActuatorDriverI2C::getGoPin() { return this->m_goPin; }

void ActuatorDriverI2C::writeRegister(int reg, int data) {
  i2c_write_reg(this->m_address, reg, data);
}

int ActuatorDriverI2C::readRegister(int reg) {
  return i2c_read(this->m_address, reg, 1);
}

ActuatorDriverType ActuatorDriverI2C::getType() { return this->m_type; }
