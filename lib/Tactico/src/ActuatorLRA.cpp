#include "ActuatorLRA.h"

int ActuatorLRA::nextID = 0;

ActuatorLRA::ActuatorLRA(std::shared_ptr<IActuatorDriver> driver,
                         int ratedVoltage, int overdriveVoltage,
                         int resonantFrequency, const std::string &name)
    : IActuator(driver, ratedVoltage, overdriveVoltage, name) {
  this->id = ++nextID;
  this->m_resonantFrequency = resonantFrequency;
  this->m_type = LRA;
}

ActuatorLRA::ActuatorLRA(std::shared_ptr<IActuatorDriver> driver,
                         int ratedVoltage, int overdriveVoltage,
                         int resonantFrequency)
    : IActuator(driver, ratedVoltage, overdriveVoltage) {
  this->id = ++nextID;
  this->m_resonantFrequency = resonantFrequency;
  this->m_name =
      std::string(ACTUATOR_LRA_DEFAULT_NAME).append(std::to_string(id));
  this->m_type = LRA;
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
}

ActuatorType ActuatorLRA::getType() { return this->m_type; }

std::shared_ptr<IActuatorDriver> ActuatorLRA::getDriver() {
  return this->m_driver;
}
