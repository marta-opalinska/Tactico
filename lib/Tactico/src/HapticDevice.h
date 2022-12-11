#pragma once
#include <Interfaces/IActuator.h>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Action.h"

/**
 * @class HapticDevice
 * @brief Class that stores parameters and methods of haptic device that consists of multiple actuators.
 * @param defaultName default name if not specified will be "device_" + id
 * @param id device identifier - count of created HapticDevice objects
 * @param m_name device custom name 
 * @param m_actuatorsList list of Actuators belonging to the Haptic Device 
 * @param m_deviceActions list of Actions belonging to the Haptic Device 
 * 
 */
class HapticDevice {
 protected:
  static int nextID;
  static const std::string defaultName;
  int id;
  std::vector<std::shared_ptr<IActuator>> m_actuatorsList;
  std::map<std::string, std::shared_ptr<Action>> m_deviceActions;

 public:
  std::string m_name;
  HapticDevice() = default;
  ~HapticDevice() = default;
  HapticDevice(std::vector<std::shared_ptr<IActuator>> actuatorsList,
               const std::string& name = "");
  HapticDevice(std::shared_ptr<IActuator> singleActuator,
               const std::string& name = "");
  void renameDevice(const std::string& name);
  void addActuator(std::shared_ptr<IActuator> actuator);
  void addActuators(std::vector<std::shared_ptr<IActuator>> actuatorsVector);
  void removeActuator(std::shared_ptr<IActuator> actuator);
  void removeActuator(int actuatorPosition);
  void removeActuator(const std::string& name);
  std::vector<std::shared_ptr<IActuator>> getActuatorsList();
  void clearActuatorsList();
  void addActions(
      std::map<std::string, std::shared_ptr<Action>> additinalDeviceActions);
  void addAction(std::shared_ptr<Action> deviceAction, std::string actionName);
  void removeAction(std::string actionName);
  void playAction(std::string actionName);
  void getActions();
  // TODO(,e) these functions
  void cleanActions();
  void startActuators();
  void stopActuators();
};
