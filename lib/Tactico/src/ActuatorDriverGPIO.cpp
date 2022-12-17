#pragma once
#include "ActuatorDriverGPIO.h"

ActuatorDriverGPIO::ActuatorDriverGPIO(int GPIO_pin) : m_GPIO_pin(GPIO_pin) {
  this->init();
  this->m_type = GPIO;
}

void ActuatorDriverGPIO::init() {
  setPinModeTactico(this->m_GPIO_pin, OUTPUT);
  std::string s = "Set GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append(" as OUTPUT.\n");
  printTactico(s);
}

void ActuatorDriverGPIO::setGPIOHigh() {
  setPinStatusTactico(this->m_GPIO_pin, 1);
  std::string s = "Actuator Driver START, GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append("\n");
  printTactico(s);
}

void ActuatorDriverGPIO::setGPIOLow() {
  setPinStatusTactico(this->m_GPIO_pin, 0);
    std::string s = "Actuator Driver STOP, GPIO ";
  s.append(std::to_string(this->m_GPIO_pin));
  s.append("\n");
  printTactico(s);
}

bool ActuatorDriverGPIO::play(std::shared_ptr<IPattern> pattern) {
  if (pattern->getType() == ePWM) {
    auto patternPWM(std::static_pointer_cast<PatternPWM>(pattern));

    for (auto m : (patternPWM->m_modulation_sequence)) {
      if (m.isOn) {
        this->setGPIOHigh();
      } else {
        this->setGPIOLow();
      }
      waitFor(m.duration);
    }
    return true;
  } else {
    printTactico(
        "Invalid argument - ActuatorDriverGPIO does not support this type of "
        "Pattern");
  }
  return false;
}

// bool ActuatorDriverGPIO::playPWM(std::shared_ptr<PatternPWM> pattern) {
//   for (auto m : pattern->m_modulation_sequence) {
//     if (m.isOn) {
//       this->setGPIOHigh();
//     } else {
//       this->setGPIOLow();
//     }
//     waitFor(m.duration);
//   }
//   return true;
// }

// void ActuatorDriverGPIO::stop() {
//   this->setGPIOLow();
//   std::string s = "Actuator Driver STOP, GPIO ";
//   s.append(std::to_string(this->m_GPIO_pin));
//   s.append("\n");
//   printTactico(s);
// }
void ActuatorDriverGPIO::setPin(int new_GPIO) {
  this->setGPIOLow();
  this->m_GPIO_pin = new_GPIO;
  this->init();
}

int ActuatorDriverGPIO::getPin() { return this->m_GPIO_pin; }

DriverType ActuatorDriverGPIO::getType() { return this->m_type; }
// void ActuatorDriverGPIO::play(IPattern pattern){

// }
