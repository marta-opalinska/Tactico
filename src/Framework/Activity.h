#pragma once
#include "Actuator.h"
#include <vector>
#include "Step.h"

class Activity
{
public:
    Activity() = delete;
    ~Activity() = default;
    std::vector<Step*> m_activitySteps;
    void addStep(Actuator *actuator, bool isStart);
    void addStep(Step* step);
    void addWait(int miliseconds);
    void addWait(StepWait* stepWait);
    // removes single step
    void removeStepByID(int stepID);
    // if the same step was duplicated it will remove all the steps that are associated with this pointer
    void removeStep(Step* step);
    // replace single step
    void replaceStepByID(Step* stepToReplace, Actuator *actuator, bool isStart);
    // if the same step was duplicated it will replace all the steps that are associated with this pointer
    void replaceStep(int stepToReplaceID, Actuator *actuator, bool isStart);
    void play();
};
