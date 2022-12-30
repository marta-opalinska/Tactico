/** Copyright 2022 <Marta Opalinska> **/

#include "ActuatorLRA.h"

int ActuatorLRA::nextID = 0;

ActuatorLRA::ActuatorLRA(std::shared_ptr<IActuatorDriver> driver,
                         float ratedVoltage, float overdriveVoltage,
                         int resonantFrequency, const std::string &name)
    : IActuator(driver, ratedVoltage, overdriveVoltage, name) {
  this->id = ++nextID;
  this->m_resonantFrequency = resonantFrequency;
  this->m_type = eLRA;
  this->configureDriver();
}

ActuatorLRA::ActuatorLRA(std::shared_ptr<IActuatorDriver> driver,
                         float ratedVoltage, float overdriveVoltage,
                         int resonantFrequency)
    : IActuator(driver, ratedVoltage, overdriveVoltage) {
  this->id = ++nextID;
  this->m_resonantFrequency = resonantFrequency;
  this->m_name =
      std::string(ACTUATOR_LRA_DEFAULT_NAME).append(std::to_string(id));
  this->m_type = eLRA;
  this->configureDriver();
}

void ActuatorLRA::configureDriver() {
  DriverType type = m_driver->getType();
  if (type == eI2C) {
    auto driverDRV2505L(std::static_pointer_cast<ActuatorDriverDRV2605LEVM>(m_driver));
    driverDRV2505L->config(eLRA, m_ratedVoltage, m_overdriveVoltage,
                           m_resonantFrequency);
  }
}

bool ActuatorLRA::play(std::shared_ptr<IPattern> pattern) {
  PatternType type = pattern->getType();
  if (type == eDRV2505L) {
    return this->m_driver->play(pattern);
  } else {
    printTactico(
        "Invalid argument - ActuatorLRA does not support this type of "
        "Pattern");
    return false;
  }
}

void ActuatorLRA::setDriver(std::shared_ptr<IActuatorDriver> driver) {
  this->m_driver = driver;
  this->configureDriver();
}

ActuatorType ActuatorLRA::getType() { return this->m_type; }

std::shared_ptr<IActuatorDriver> ActuatorLRA::getDriver() {
  return this->m_driver;
}
