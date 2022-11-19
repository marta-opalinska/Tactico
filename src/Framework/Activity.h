#include "Actuator.h"
#include <vector>
#include "Step.cpp"

class Activity
{
private:
     std::vector<Step> activitySteps;
    /* data */

public:
    Activity() = delete;
    ~Activity() = default;
    void addStep(Actuator *actuator, bool isStart);
    void addWait(int miliseconds);
    void removeStep(int stepID);
    void replaceStep(int stepID, Actuator *actuator, bool isStart);
    void play();
};
