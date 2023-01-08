/** Copyright 2022 <Marta Opalinska> **/

#include "ActuatorDriverGPIO.h"

ActuatorDriverGPIO::ActuatorDriverGPIO(int GPIO_pin) : m_GPIO_pin(GPIO_pin) {
  this->init();
  this->m_needsPreconfigration = false;
  this->m_type = eGPIO;
}

void ActuatorDriverGPIO::init() {
  setPinModeTactico(this->m_GPIO_pin, TACTICO_OUTPUT);
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

void ActuatorDriverGPIO::test() {
  this->setGPIOHigh();
  waitFor(50);
  this->setGPIOLow();
  waitFor(50);
  this->setGPIOHigh();
  waitFor(50);
  this->setGPIOLow();
  waitFor(50);
  this->setGPIOHigh();
  waitFor(50);
  this->setGPIOLow();
}

void ActuatorDriverGPIO::setPin(int new_GPIO) {
  this->setGPIOLow();
  this->m_GPIO_pin = new_GPIO;
  this->init();
}

int ActuatorDriverGPIO::getPin() { return this->m_GPIO_pin; }

void ActuatorDriverGPIO::resetPreRunConfiguration() {
  // can be ignored - no configuration to reset
}

ActuatorDriverType ActuatorDriverGPIO::getType() { return this->m_type; }
