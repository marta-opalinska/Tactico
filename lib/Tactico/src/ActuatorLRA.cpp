#include "ActuatorLRA.h"

int ActuatorLRA::nextID = 0;
// const char ActuatorLRA::defaultName[14] = "actuatorERM_";
const std::string ActuatorLRA::defaultName = "actuator_";

ActuatorLRA::ActuatorLRA(std::shared_ptr<IActuatorDriver> driver,
                         const std::string &name)
    : IActuator(driver, name) {
  this->id = ++nextID;
  this->m_type = ERM;
}

ActuatorLRA::ActuatorLRA(std::shared_ptr<IActuatorDriver> driver)
    : IActuator(driver) {
  this->id = ++nextID;
  this->m_name = std::string(this->defaultName).append(std::to_string(id));
  this->m_type = ERM;
}

bool ActuatorLRA::play(std::shared_ptr<IPattern> pattern) {
  PatternType type = pattern->getType();
  if ( type == ePWM  || type == eDRV2505L) {
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
