#include "ActuatorERM.h"

int ActuatorERM::nextID = 0;
std::string const ActuatorERM::defaultName = "actuator_";

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver,
                         const std::string &name)
    : m_driver(driver), m_name(name) {
  this->id = ++nextID;
}

ActuatorERM::ActuatorERM(std::shared_ptr<IActuatorDriver> driver)
    : m_driver(driver) {
  this->id = ++nextID;
  this->m_name = defaultName;
  this->m_name.append(std::to_string(id));
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
