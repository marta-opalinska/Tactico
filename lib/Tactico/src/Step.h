#pragma once
#include <Interfaces/IActuator.h>
#include "HardwareLayer.h"
#include "string.h"

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
    StepActuator(std::shared_ptr<IActuator> actuator, bool isStart);
    ~StepActuator() = default;
    std::shared_ptr<IActuator> m_actuator;
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
