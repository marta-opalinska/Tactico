#include "ActuatorERM.h"

int ActuatorERM::nextID = 0;
// const char ActuatorERM::defaultName[14] = "actuatorERM_";
const std::string ActuatorERM::defaultName = "actuator_";

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver,
                         const std::string &name)
    : IActuator(driver, name) {
  this->id = ++nextID;
  this->m_type = ERM;
}

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver)
    : IActuator(driver) {
  this->id = ++nextID;
  this->m_name = std::string(this->defaultName).append(std::to_string(id));
  this->m_type = ERM;
}

bool ActuatorERM::play(std::shared_ptr<IPattern> pattern) {
  PatternType type = pattern->getType();
  if ( type == ePWM  || type == eDRV2505L) {
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
}

ActuatorType ActuatorERM::getType() { return this->m_type; }

std::shared_ptr<IActuatorDriver> ActuatorERM::getDriver() {
  return this->m_driver;
}
