#pragma once
#include "ActuatorDriverI2C.h"

bool ActuatorDriverI2C::m_I2C_Initialised = true;

ActuatorDriverI2C::ActuatorDriverI2C(int goPin) : m_goPin(goPin) {
  this->init();
  this->m_usesGoPinFlag = true;
}

void ActuatorDriverI2C::init() {
  if (!this->m_I2C_Initialised) {
    i2c_begin();
  }
  this->m_type = I2C;
  // initDRV2505();
}

void ActuatorDriverI2C::initDRV2505L() {
  writeRegister(DRV2605_REG_MODE, 0x00);  // out of standby

  writeRegister(DRV2605_REG_RTPIN, 0x00);  // no real-time-playback

  writeRegister(DRV2605_REG_WAVESEQ1, 1);  // strong click
  writeRegister(DRV2605_REG_WAVESEQ2, 0);  // end sequence

  writeRegister(DRV2605_REG_OVERDRIVE, 0);  // no overdrive

  writeRegister(DRV2605_REG_SUSTAINPOS, 0);
  writeRegister(DRV2605_REG_SUSTAINNEG, 0);
  writeRegister(DRV2605_REG_BREAK, 0);
  writeRegister(DRV2605_REG_AUDIOMAX, 0x64);

    // turn off N_ERM_LRA
  writeRegister(DRV2605_REG_FEEDBACK,
                 readRegister(DRV2605_REG_FEEDBACK) & 0x7F);
  // turn on ERM_OPEN_LOOP
  writeRegister(DRV2605_REG_CONTROL3,
                 readRegister(DRV2605_REG_CONTROL3) | 0x20);
}

void ActuatorDriverI2C::writeRegister(int reg, int data) {
  i2c_write(DRV2605_ADDR, reg, data);
}

int ActuatorDriverI2C::readRegister(int reg) {
  return i2c_read(DRV2605_ADDR, reg, 1);
} 

// void ActuatorDriverI2C::setGPIOHigh() {
//   setPinStatusTactico(this->m_GPIO_pin, 1);
// }

// void ActuatorDriverI2C::setLowGPIO() {
//   setPinStatusTactico(this->m_GPIO_pin, 0);
// }

// void ActuatorDriverI2C::play() {
//   this->setGPIOHigh();
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

// void ActuatorDriverI2C::play(IPattern pattern){

// }
