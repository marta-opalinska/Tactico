#pragma once
#include "Actuator.h"
#include "Arduino.h"

class Step
{
protected:
    Step() = default;
    ~Step() = default;

public:
    void play();
};

class StepActuator : public Step
{
protected:
    StepActuator() = default;

public:
    // tep() = default;
    StepActuator(Actuator& actuator, bool isStart);
    ~StepActuator() = default;
    Actuator& m_actuator;
    bool m_isStart;
    void play();
};

class StepWait : public Step
{
protected:
    StepWait() = default;

public:
    // tep() = default;
    StepWait(unsigned int miliseconds);
    ~StepWait() = default;
    unsigned int m_waitTime;
    void play();
};
