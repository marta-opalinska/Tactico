/** Copyright 2022 <Marta Opalinska> **/

#include "HapticDevice.h"

int HapticDevice::nextID = 0;
const std::string HapticDevice::defaultName = "device_";

HapticDevice::HapticDevice(
    std::vector<std::shared_ptr<IActuator>> actuatorsList,
    const std::string &name /*=""*/)
    : m_actuatorsList(actuatorsList) {
  this->id = ++nextID;
  if (name == "") {
    this->m_name = defaultName;
    this->m_name.append(std::to_string(id));
  } else {
    this->m_name = name;
  }
}

HapticDevice::HapticDevice(std::shared_ptr<IActuator> signleActuator,
                           const std::string &name /*=""*/) {
  this->m_actuatorsList.push_back(signleActuator);
  this->id = ++nextID;
  if (name == "") {
    this->m_name = defaultName;
    this->m_name.append(std::to_string(id));
  } else {
    this->m_name = name;
  }
}

void HapticDevice::addActuator(std::shared_ptr<IActuator> actuator) {
  this->m_actuatorsList.push_back(actuator);
}

void HapticDevice::addActuators(
    std::vector<std::shared_ptr<IActuator>> actuatorsVector) {
  for (auto ac : actuatorsVector) {
    this->addActuator(ac);
  }
}

void HapticDevice::removeActuator(std::shared_ptr<IActuator> actuator) {
  // v.erase(std::remove_if(v.begin(), v.end(), IsOdd), v.end());
  // The erase–remove idiom which is a common C++ technique
  this->m_actuatorsList.erase(
      std::remove(this->m_actuatorsList.begin(), this->m_actuatorsList.end(),
                  actuator),
      this->m_actuatorsList.end());
}

// Index calculated from 0 an according to adding to the list
void HapticDevice::removeActuator(int actuatorPosition) {
  this->m_actuatorsList.erase(this->m_actuatorsList.begin() + actuatorPosition);
}

// Remove based on actuator name
void HapticDevice::removeActuator(const std::string &name) {
  int i = 0;
  for (auto &ac : this->m_actuatorsList) {
    if (ac->m_name == name) {
      this->removeActuator(i);
    }
    i++;
  }
}

// Provides a list of actuators that are a part of the haptics device
std::vector<std::shared_ptr<IActuator>> HapticDevice::getActuatorsList() {
  return this->m_actuatorsList;
}

// Clean actuators list
void HapticDevice::clearActuatorsList() { this->m_actuatorsList.clear(); }

void HapticDevice::addActions(
    std::map<std::string, std::shared_ptr<Action>> deviceActions) {
  this->m_deviceActions.insert(deviceActions.begin(), deviceActions.end());
}

void HapticDevice::addAction(std::shared_ptr<Action> deviceAction,
                             std::string actionName) {
  this->m_deviceActions[actionName] = deviceAction;
}

void HapticDevice::configureAction(std::string actionName) {
  // checking if an action exists
  if (m_deviceActions.count(actionName)) {
    this->m_deviceActions[actionName]->configure();
  } else {
    printTactico("WARNING: Action not found \n");
  }
}

void HapticDevice::configureAndPlayAction(std::string actionName) {
  // checking if an action exists
  if (this->m_deviceActions.count(actionName)) {
    this->m_deviceActions[actionName]->configureAndPlay();
  } else {
    printTactico("WARNING: Action not found \n");
  }
}

void HapticDevice::playAction(std::string actionName) {
  // checking if an action exists
  if (this->m_deviceActions.count(actionName)) {
    this->m_deviceActions[actionName]->play();
  } else {
    printTactico("WARNING: Action not found \n");
  }
}

void HapticDevice::resetActuatorsPreRunConfiguration() {
  for (auto actuator : this->m_actuatorsList) {
    actuator->getDriver()->resetPreRunConfiguration();
  }
}

void HapticDevice::removeAction(std::string actionName) {
  this->m_deviceActions.erase(actionName);
}

std::map<std::string, std::shared_ptr<Action>> HapticDevice::getActions() {
  return this->m_deviceActions;
}

void HapticDevice::clearActions() { this->m_deviceActions.clear(); }

void HapticDevice::testActuators() {
  for (auto &ac : m_actuatorsList) {
    ac->test();
    waitFor(2000);
  }
}

// void HapticDevice::stopActuators() {
//   for (auto &ac : m_actuatorsList) {
//     ac->stop();
//   }
// }
