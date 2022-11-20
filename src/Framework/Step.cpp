#include "Step.h"

StepActuator::StepActuator(Actuator& actuator, bool isStart)
    : m_actuator(actuator)
    , m_isStart(isStart){}

void StepActuator::play()
{
    if (this->m_isStart)
    {
        this->m_actuator->start();
    }
    else
    {
        this->m_actuator->stop();
    }
}

StepWait::StepWait(unsigned int miliseconds)
    : m_waitTime(miliseconds){}

void StepWait::play()
{
    delay(this->m_waitTime);
};