/** copyright 2022 <Marta Opalinska> **/
#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IPattern.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "ActuatorDriverDRV2605LEVM.h"
#include "Step.h"

// the limit of DRV2605L driver when it comes to the steps saving
#define MAX_STEPS 5

/**
 * @brief
 *
 */

struct actuatorConfigData {
  // the time (in miliseconds) passed from the last time the actuator was
  // configured with play pattern (needed for waitTime preconfiguration)
  int timeFromLastPattern;
  // the latest used actuators patttern slot
  int currentPatternSlot;
};

/**
 * @class Action
 * @brief Class that can store multistep activity that can be performed on
 * multiple actuators
 * @details There are two typed of steps that an action can consist of :
 * WaitStepImpl (delay between two actions) and StepStepActuator (action that is
 * performed on a specific Actuator)
 * @param m_activitySteps vector of steps that belongs to the activity.
 * @param m_actuators list of all the actuators that are in the action
 */
class Action {
 private:
  std::vector<std::shared_ptr<IStep>> m_activitySteps;
  std::vector<std::shared_ptr<IActuator>> m_actuators;
  std::vector<int> m_goPins;
  int m_nextStepID;
  void configureActuatorDriver(std::shared_ptr<IActuatorDriver> actuatorDriver,
                               int slotCounter,
                               std::shared_ptr<IPattern> pattern);
  void configureActuatorDriverWait(
      std::shared_ptr<IActuatorDriver> actuatorDriver, int patternSlot,
      int waitTime);

 public:
  Action();
  ~Action() = default;
  void addStep(std::shared_ptr<IActuator> actuator,
               std::shared_ptr<IPattern> pattern);
  void addStep(std::shared_ptr<IStep> step);
  void addWait(int miliseconds);
  void addWait(std::shared_ptr<WaitStepImpl> stepWait);
  std::vector<std::shared_ptr<IStep>> getSteps();
  void setSteps(std::vector<std::shared_ptr<IStep>> activitySteps);
  void configureAction();
  void clear();
  void play();
  void ConfigureAndPlay();
};
