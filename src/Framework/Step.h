#pragma once
#include "Actuator.h"
#include "Arduino.h"

class IStep
{
public:
    virtual void play() = 0;
    virtual void printStep() = 0;
};

class StepActuator : public IStep
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
    void printStep();
};

class StepWait : public IStep
{
protected:
    StepWait() = default;

public:
    // tep() = default;
    StepWait(unsigned int miliseconds);
    ~StepWait() = default;
    unsigned int m_waitTime;
    void play();
    void printStep();
};
