#include "Step.h"
// class StepWait{

// }

// class Step{

// }

StepActuator::StepActuator(Actuator *actuator, bool isStart)
{
    this->actuator = actuator;
    this->isStart = isStart;
}

void StepActuator::play()
{
    if (this->isStart)
    {
        this->actuator->start();
    }
    else
    {
        this->actuator->stop();
    }
}

StepWait::StepWait(unsigned int miliseconds)
{
    this->waitTime = miliseconds;
}

void StepWait::play()
{
    delay(this->waitTime);
};