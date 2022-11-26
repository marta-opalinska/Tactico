#include "Step.h"
#include "string.h"

StepActuator::StepActuator(Actuator& actuator, bool isStart)
    : m_actuator(actuator)
    , m_isStart(isStart){}

void StepActuator::play()
{
    if (this->m_isStart)
    {
        this->m_actuator.start();
    }
    else
    {
        this->m_actuator.stop();
    }
}

void StepActuator::printStep()
{
    Serial.println(String(this->m_actuator.m_name.c_str()) + " : " + (this->m_isStart ? "Start": "Stop"));
    // return ", " +this->m_actuator.m_name + " : " + (this->m_isStart ? "Start": "Stop");
}

StepWait::StepWait(unsigned int miliseconds)
    : m_waitTime(miliseconds){}

void StepWait::play()
{
    Serial.println("Waiting for : " + String(this->m_waitTime));
    delay(this->m_waitTime);
};

void StepWait::printStep()
{
    Serial.println("Wait for : " + String(this->m_waitTime));
    // Serial.print(

    //     this.
    // );
}
