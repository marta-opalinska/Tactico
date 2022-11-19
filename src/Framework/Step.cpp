#include "Actuator.h"
#include "Arduino.h"

// class StepWait{

// }

// class Step{

// }

// struct {
//   Actuator* actuator;
//   bool isStart;
// } Step;

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
    StepActuator(Actuator *actuator, bool isStart);
    ~StepActuator() = default;
    Actuator *actuator;
    bool isStart;
    void play();
};

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

class StepWait : public Step
{
protected:
    StepWait() = default;

public:
    // tep() = default;
    StepWait(int miliseconds);
    ~StepWait() = default;
    int waitTime;
    void play();
};

StepWait::StepWait(int miliseconds)
{
    this->waitTime = miliseconds;
}

void StepWait::play()
{
    delay(this->waitTime);
}