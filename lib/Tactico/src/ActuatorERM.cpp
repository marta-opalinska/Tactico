#include "ActuatorERM.h"

// int ActuatorERM::nextID = 0;

// ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver,
//                          const std::string &name)
//     : IActuator(driver, name) {
//   this->id = ++nextID;
// }

// ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver)
//     : IActuator(driver,
//     std::string(IActuator::defaultName).append(std::to_string(nextID))) {
//   this->id = ++nextID;
// }

// void ActuatorERM::start() {
//   std::string s = "Actuator ";
//   s.append(this->m_name);
//   s.append(": \n");
//   printTactico(s);
//   this->m_driver->startActuator();
// }

// void ActuatorERM::stop() {
//   std::string s = "Actuator ";
//   s.append(this->m_name);
//   s.append(": \n");
//   printTactico(s);
//   this->m_driver->stopActuator();
// }

// void ActuatorERM::setDriver(std::shared_ptr<IActuatorDriver> driver) {
//   this->m_driver = driver;
// }

int ActuatorERM::nextID = 0;
// const char ActuatorERM::defaultName[14] = "actuatorERM_";
const std::string ActuatorERM::defaultName = "actuator_";

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver,
                         const std::string &name)
    : IActuator(driver, name) {
  this->id = ++nextID;
}

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver)
    : IActuator(driver) {
  this->id = ++nextID;
  this->m_name = std::string(this->defaultName).append(std::to_string(id));
  // this->m_name.append(std::to_string(id));
}

void ActuatorERM::start() {
  std::string s = "Actuator ";
  s.append(this->m_name);
  s.append(": \n");
  printTactico(s);
  this->m_driver->startActuator();
}

void ActuatorERM::stop() {
  std::string s = "Actuator ";
  s.append(this->m_name);
  s.append(": \n");
  printTactico(s);
  this->m_driver->stopActuator();
}

void ActuatorERM::setDriver(std::shared_ptr<IActuatorDriver> driver) {
  this->m_driver = driver;
}