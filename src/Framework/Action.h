#pragma once
#include "Actuator.h"
#include <memory>
#include <vector>
#include "Step.h"
#include "Actuator.h"

class Action
{
public:
    Action() = default;
    ~Action() = default;
    std::vector<std::shared_ptr<IStep>> m_activitySteps;
    void addStep(Actuator& actuator, bool isStart);
    void addStep(std::shared_ptr<IStep> step);
    void addWait(int miliseconds);
    void addWait(std::shared_ptr<StepWait> stepWait);
    // removes single step
    void removeStep(int stepPosition);
    // if the same step was duplicated it will remove all the steps that are associated with this pointer
    // void removeStep(Step* step);
    // replace single step
    // void replaceStepByID(Step* stepToReplace, Actuator *actuator, bool isStart);
    // if the same step was duplicated it will replace all the steps that are associated with this pointer
    // void replaceStep(int stepToReplaceID, Actuator *actuator, bool isStart);
    void play();
};
