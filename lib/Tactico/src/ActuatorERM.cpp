/** Copyright 2022 <Marta Opalinska> **/

#include "ActuatorERM.h"

int ActuatorERM::nextID = 0;

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver,
                         float ratedVoltage, float overdriveVoltage,
                         const std::string &name)
    : IActuator(driver, ratedVoltage, overdriveVoltage, name) {
  this->id = ++nextID;
  this->m_type = eERM;
  this->configureDriver();
}

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver,
                         float ratedVoltage, float overdriveVoltage)
    : IActuator(driver, ratedVoltage, overdriveVoltage) {
  this->id = ++nextID;
  this->m_name =
      std::string(ACTUATOR_ERM_DEFAULT_NAME).append(std::to_string(id));
  this->m_type = eERM;
  this->configureDriver();
}

void ActuatorERM::configureDriver() {
  ActuatorDriverType type = this->m_driver->getType();
  if (type == eI2C) {
    auto driverDRV2505L(std::static_pointer_cast<ActuatorDriverDRV2605LEVM>(m_driver));
    driverDRV2505L->config(eERM, this->m_ratedVoltage, this->m_overdriveVoltage,
                           300);
  }
}

bool ActuatorERM::play(std::shared_ptr<IPattern> pattern) {
  PatternType type = pattern->getType();
  if (type == ePWM || type == eDRV2505L) {
    return this->m_driver->play(pattern);
  } else {
    printTactico(
        "Invalid argument - ActuatorERM does not support this type of "
        "Pattern");
    return false;
  }
}

// bool ActuatorERM::playPWM(std::shared_ptr<PatternPWM> pattern) {
//   return this->m_driver->play(pattern);
// }

// void ActuatorERM::stop() {
//   std::string s = "Actuator ";
//   s.append(this->m_name);
//   s.append(": \n");
//   printTactico(s);
//   this->m_driver->stop();
// }

void ActuatorERM::setDriver(std::shared_ptr<IActuatorDriver> driver) {
  this->m_driver = driver;
  this->configureDriver();
}

ActuatorType ActuatorERM::getType() { return this->m_type; }

std::shared_ptr<IActuatorDriver> ActuatorERM::getDriver() {
  return this->m_driver;
}
