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
 * @brief Structure for actiator configuation data. It contains the time (in
 * miliseconds) that passed from the last time the actuator was configured with
 * play pattern (needed for waitTime preconfiguration) and the latest used actuators patttern slot.
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
 * @brief Class that can store multistep activity that can be performed on
 * multiple actuators
 * @details There are two typed of steps that an action can consist of :
 * WaitStep (delay between two actions) and StepStepActuator (action that is
 * performed on a specific Actuator)
 * @param m_activitySteps vector of steps that belongs to the activity.
 * @param m_actuators list of all the actuators that are in the action
 */
class Action {
 private:
  std::vector<std::shared_ptr<IStep>> m_activitySteps;
  std::set<std::shared_ptr<IActuator>> m_actuators;
  std::set<int> m_goPins;
  int m_nextStepID;
  void configureActuatorDriver(std::shared_ptr<IActuatorDriver> actuatorDriver,
                               int slotCounter,
                               std::shared_ptr<IPattern> pattern);
  void configureActuatorDriverWait(
      std::shared_ptr<IActuatorDriver> actuatorDriver, int patternSlot,
      int waitTime);
  void activateGoPins();
  void deactivateGoPins();

 public:
  Action();
  ~Action() = default;
  void addStep(std::shared_ptr<IActuator> actuator,
               std::shared_ptr<IPattern> pattern);
  void addStep(std::shared_ptr<IStep> step);
  void addWait(int miliseconds);
  void addWait(std::shared_ptr<WaitStep> stepWait);
  std::vector<std::shared_ptr<IStep>> getSteps();
  void setSteps(std::vector<std::shared_ptr<IStep>> activitySteps);
  void configureAction();
  void clear();
  void play();
  void ConfigureAndPlay();
};
