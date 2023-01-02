/** copyright 2022 <Marta Opalinska> **/
#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "ActuatorDriverDRV2605LEVM.h"
#include "ActuatorStep.h"
#include "WaitStep.h"

/**
 * @brief Structure for actuator configuation data. It contains the time (in
 * miliseconds) that passed from the last time the actuator was configured with
 * play pattern (needed for waitTime preconfiguration) and the latest used
 * actuators patttern slot. Actuator driver can have limited number of pattern
 * slots that can be hold in the memory. Each driver slots are played one by one
 * when the "go" pin is triggered.
 *
 */
typedef struct {
  // the time (in miliseconds) passed from the last time the actuator was
  // configured with play pattern (needed for waitTime preconfiguration)
  int timeFromLastPattern;
  // the latest used actuators patttern slot
  int currentPatternSlot;
} actuatorConfigData;

/**
 * @class Action
 * @brief Class that stores multistep activity that can be performed on
 * multiple actuators
 * @details There are two typed of steps that an action can consist of :
 * WaitStep (delay between two actions) and StepStepActuator (action that is
 * performed on a specific Actuator)
 * @param m_activitySteps vector of steps that belongs to the activity.
 * @param m_actuators list of all the actuators that are in the action
 */
class Action {
 private:
  /**
   * Shared pointers to activity steps that the action involve
   */
  std::vector<std::shared_ptr<IStep>> m_activitySteps;

  /**
   *  Shared pointers to all the actuators involved in the action
   */
  std::set<std::shared_ptr<IActuator>> m_actuators;

  /**
   * Set of all GPIO "go" pins that need to be triggered when action is played
   *
   */
  std::set<int> m_goPins;

  /**
   * Unique ID for an action.
   */
  int m_nextStepID;

  /**
   * @brief Configure the actuator driver with specific pattern before the
   * action is played. That function applies only to actuator drivers in which
   * m_needsPreconfigration flag is set up
   *
   * @param actuatorDriver driver to configure
   * @param slotCounter slot to write a pattern
   * @param pattern pattern that is suitable for the driver
   */
  void configureActuatorDriver(std::shared_ptr<IActuatorDriver> actuatorDriver,
                               int slotCounter,
                               std::shared_ptr<IPattern> pattern);

  /**
   * @brief Preconfigure the actuator driver with a wait time. That function
   * applies only to actuator drivers in which m_needsPreconfigration flag is
   * set up.
   *
   * @param actuatorDriver driver to configure
   * @param patternSlot slot to write a wait time
   * @param waitTime a time to wait (in miliseconds)
   */
  void configureActuatorDriverWait(
      std::shared_ptr<IActuatorDriver> actuatorDriver, int patternSlot,
      int waitTime);

  /**
   * @brief Activate "go" pins of all actuators that were previosuly configured.
   *
   */
  void activateGoPins();
  /**
   * @brief Deactvated "go" pins of all actuators that were previosuly
   * configured.
   *
   */
  void deactivateGoPins();

 public:
  Action();

  ~Action() = default;

  /**
   * @brief Add step for an Action.
   *
   * @param actuator shared pointer to the actuator
   * @param pattern pattern to perform
   */
  void addStep(std::shared_ptr<IActuator> actuator,
               std::shared_ptr<IPattern> pattern);
  /**
   * @brief Add step for an Action.
   *
   * @param step step to add
   */
  void addStep(std::shared_ptr<IStep> step);

  /**
   * @brief Add wait time to the Action
   *
   * @param miliseconds time to wait (in miliseconds)
   */
  void addWait(int miliseconds);

  /**
   * @brief Add waitStep to the Action
   *
   * @param waitStep waitStep to add
   */
  void addWait(std::shared_ptr<WaitStep> waitStep);

  /**
   * @brief Get the vector of all Steps in the Action
   *
   * @return std::vector<std::shared_ptr<IStep>> Steps in the Action
   */
  std::vector<std::shared_ptr<IStep>> getSteps();

  /**
   * @brief Set all Steps in one go.
   *
   * @param activitySteps Steps to add to the Action
   */
  void setSteps(std::vector<std::shared_ptr<IStep>> activitySteps);

  /**
   * @brief Configure all the drivers in which m_needsPreconfigration flag is
   * set up. In that case the function need to be called before play()!
   */
  void configure();

  /**
   * @brief Clear Action steps.
   *
   */
  void clear();

  /**
   * @brief Play the action. If any drivers with m_needsPreconfigration flag
   * set up, a configure() need to be called first!
   *
   */
  void play();

  /**
   * @brief Configures drivers with m_needsPreconfigration flag
   * set up and plays the action.
   *
   */
  void ConfigureAndPlay();
};
