/** copyright 2022 <Marta Opalinska> **/
#include "Action.h"

Action::Action() { this->m_nextStepID = 0; }

void Action::addStep(std::shared_ptr<IActuator> actuator,
                     std::shared_ptr<IPattern> pattern) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  this->m_activitySteps.push_back(
      std::make_shared<ActuatorStepImpl>(actuator, pattern));
  // saving a vector of all the actator that are a part of this action
  this->m_actuators.push_back(actuator);
  this->m_nextStepID++;
}

void Action::addStep(std::shared_ptr<IStep> step) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  if (step->getType() == eActuatorStep) {
    auto actuatorStep(std::static_pointer_cast<ActuatorStepImpl>(step));
    // saving a vector of all the actator that are a part of this action
    this->m_actuators.push_back(actuatorStep->m_actuator);
  }
  this->m_activitySteps.push_back(step);
  this->m_nextStepID++;
}

void Action::addWait(int miliseconds) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  this->m_activitySteps.push_back(std::make_shared<WaitStepImpl>(miliseconds));
  this->m_nextStepID++;
}

void Action::addWait(std::shared_ptr<WaitStepImpl> stepWait) {
  if (m_nextStepID >= MAX_STEPS) {
    printTactico("Action maximum step excided.");
    return;
  }
  this->m_activitySteps.push_back(stepWait);
  this->m_nextStepID++;
}

void Action::clear() {
  this->m_nextStepID = 0;
  this->m_activitySteps.clear();
  this->m_actuators.clear();
}

std::vector<std::shared_ptr<IStep>> Action::getSteps() {
  return this->m_activitySteps;
}

void Action::setSteps(std::vector<std::shared_ptr<IStep>> activitySteps) {
  this->m_activitySteps = activitySteps;
}

void Action::configureActuatorDriver(
    std::shared_ptr<IActuatorDriver> actuatorDriver, int slotCounter,
    std::shared_ptr<IPattern> pattern) {
  switch (actuatorDriver->getType()) {
    case eDRV2505L_EVBOARD: {
      // set waveform for DRV2605L driver
      auto actuatorDriverDRV2605LEVM(
          std::static_pointer_cast<ActuatorDriverDRV2605LEVM>(actuatorDriver));
      actuatorDriverDRV2605LEVM->setWaveform(slotCounter, pattern);
      // adding goPins to trigger for a play - multiple actuator can
      // be on the same goPin
      m_goPins.push_back(actuatorDriverDRV2605LEVM->getGoPin());
      break;
    }
    default: {
      printTactico("No configuration setup found. \n");
      break;
    }
  }
}

void Action::configureActuatorDriverWait(
    std::shared_ptr<IActuatorDriver> actuatorDriver, int patternSlot,
    int waitTime) {
  switch (actuatorDriver->getType()) {
    case eDRV2505L_EVBOARD: {
      // set waveform for DRV2605L driver
      auto actuatorDriverDRV2605LEVM(
          std::static_pointer_cast<ActuatorDriverDRV2605LEVM>(actuatorDriver));
      // set wait time
      actuatorDriverDRV2605LEVM->setWait(patternSlot, waitTime);
      break;
    }
    default: {
      printTactico("No configuration setup found. \n");
      break;
    }
  }
}

// TODO MAX STEPS

void Action::configureAction() {
  // creating a map linking each actuator in the action with the time (in
  // miliseconds) passed from the last time the actuator was played (needed for
  // waitTime preconfiguration) and the latest used actuator's patttern slot
  std::map<std::shared_ptr<IActuator>, actuatorConfigData> actuatorsConfigData;
  for (auto actuator : this->m_actuators) {
    // actuatorsConfigData.insert(std::make_pair(actuator, {{0, 0}}));
    actuatorsConfigData[actuator] = {0, 0};
  }
  // iterate through all the steps
  for (auto step : this->m_activitySteps) {
    step->printStep();

    switch (step->getType()) {
      case eActuatorStep: {
        auto actuatorStep(std::static_pointer_cast<ActuatorStepImpl>(step));
        auto actuatorDriver = actuatorStep->m_actuator->getDriver();
        // checking if actuator needs to be preconfigured for an action
        if (actuatorDriver->m_needsPreconfigration) {
          // checking if there should be wait added before the pattern action
          if (actuatorsConfigData[actuatorStep->m_actuator]
                  .timeFromLastPattern != 0) {
            // configuring wait
            this->configureActuatorDriverWait(
                actuatorDriver,
                actuatorsConfigData[actuatorStep->m_actuator]
                    .currentPatternSlot,
                actuatorsConfigData[actuatorStep->m_actuator]
                    .timeFromLastPattern);
            // reseting wait time
            actuatorsConfigData[actuatorStep->m_actuator].timeFromLastPattern =
                0;
            // increasing a slot counter
            actuatorsConfigData[actuatorStep->m_actuator].currentPatternSlot++;
          }
          // configuring a pattern
          this->configureActuatorDriver(
              actuatorDriver,
              actuatorsConfigData[actuatorStep->m_actuator].currentPatternSlot,
              actuatorStep->m_pattern);
          actuatorsConfigData[actuatorStep->m_actuator].currentPatternSlot++;
        }
        break;
      }
      case eWaitStep: {
        auto waitStep(std::static_pointer_cast<WaitStepImpl>(step));
        for (auto actuator : this->m_actuators) {
          actuatorsConfigData[actuator].timeFromLastPattern +=
              waitStep->m_waitTime;
        }
        break;
      }
      default: {
        printTactico("Invalid Action Step. \n");
        break;
      }
    }
  }
}
void Action::play() {
  for (auto step : this->m_activitySteps) {
    step->printStep();
    step->play();
  }
}

void Action::ConfigureAndPlay() {
  this->configureAction();
  this->play();
}
