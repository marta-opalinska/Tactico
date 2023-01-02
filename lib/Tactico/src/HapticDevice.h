/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuator.h>
#include <SPI.h>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Action.h"

/**
 * @class HapticDevice
 * @brief Class that stores parameters and methods of haptic device that
 * consists of multiple actuators.
 * @param defaultName default name if not specified will be "device_" + id
 * @param id device identifier - count of created HapticDevice objects
 * @param m_name device custom name
 * @param m_actuatorsList list of Actuators belonging to the Haptic Device
 * @param m_deviceActions list of Actions belonging to the Haptic Device
 *
 */
class HapticDevice {
 protected:
  /**
   * Unique ID setter.
   */
  static int nextID;

  /**
   * default name (if custom name not specified)
   * "device_" + id
   *
   */
  static const std::string defaultName;

  /**
   * unique identifier
   */
  int id;

  /**
   * list of actuators that are a part of a haptic device
   */
  std::vector<std::shared_ptr<IActuator>> m_actuatorsList;

  /**
   * list of action that can be performed on this haptic device
   */
  std::map<std::string, std::shared_ptr<Action>> m_deviceActions;

 public:
  /**
   * custom device name
   */
  std::string m_name;
  HapticDevice() = default;
  ~HapticDevice() = default;
  /**
   * @brief Construct a new Haptic Device object
   *
   * @param actuatorsList list of actuators to add to the haptic device
   * @param name custom name
   */
  HapticDevice(std::vector<std::shared_ptr<IActuator>> actuatorsList,
               const std::string& name = "");

  /**
   * @brief Construct a new Haptic Device object
   *
   * @param singleActuator actuator to add to the haptic device
   * @param name custom name
   */
  HapticDevice(std::shared_ptr<IActuator> singleActuator,
               const std::string& name = "");

  /**
   * @brief Add actuator to the haptic device
   *
   * @param actuator actuator to add
   */
  void addActuator(std::shared_ptr<IActuator> actuator);

  /**
   * @brief Add actuators to the haptic device
   *
   * @param actuatorsVector vector of actuators to add
   */
  void addActuators(std::vector<std::shared_ptr<IActuator>> actuatorsVector);

  /**
   * @brief Remove actuator from the haptic device
   *
   * @param actuator actuator to remove
   */
  void removeActuator(std::shared_ptr<IActuator> actuator);

  /**
   * @brief Remove actuator from the haptic device based on actuator position in
   * the m_actuatorsList
   *
   * @param actuatorPosition position of actuator to remove
   */
  void removeActuator(int actuatorPosition);

  /**
   * @brief Remove actuator from the haptic device
   *
   * @param name name of actuator to remove
   */
  void removeActuator(const std::string& name);

  /**
   * @brief Get the the list of all actuators that are a part of haptic device.
   *
   * @return std::vector<std::shared_ptr<IActuator>>
   */
  std::vector<std::shared_ptr<IActuator>> getActuatorsList();

  /**
   * @brief Test the vibration of all actuators that are a part of haptic
   * device.
   *
   */
  void testActuators();

  /**
   * @brief Clear the list of actuators.
   *
   */
  void clearActuatorsList();

  /**
   * @brief Assign a list of actions to the device.
   *
   * @param deviceActions map of action name and Action object.
   */
  void addActions(std::map<std::string, std::shared_ptr<Action>> deviceActions);

  /**
   * @brief Assign action to the device.
   *
   * @param deviceAction Action object to add
   * @param actionName name of the action
   */
  void addAction(std::shared_ptr<Action> deviceAction, std::string actionName);

  /**
   * @brief Remove the action from m_deviceActions list.
   *
   * @param actionName name of the action to remove
   */
  void removeAction(std::string actionName);

  /**
   * @brief Clear m_deviceActions list.
   *
   */
  void clearActions();

  /**
   * @brief Configures an Action if any of the drivers has
   * m_needsPreconfigration flag set up.
   *
   * @param actionName name of the action to configure
   */
  void configure(std::string actionName);

  /**
   * @brief Play the action. If any drivers with m_needsPreconfigration flag
   * set up, a configure() need to be called first!
   *
   * @param actionName ame of the action to play
   */
  void playAction(std::string actionName);

  /**
   * @brief Configures the action and plays it.
   *
   * @param actionName ame of the action to configure and play
   */
  void configureAndPlayAction(std::string actionName);

  /**
   * @brief Get the Actions object
   *
   * @return std::map<std::string, std::shared_ptr<Action>>
   */
  std::map<std::string, std::shared_ptr<Action>> getActions();
};
