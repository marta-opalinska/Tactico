#pragma once
#include "HardwareLayer.h"

class IActuatorDriver
{
public:
	virtual void initDriver() = 0;
	virtual void startActuator() = 0;
	virtual void stopActuator() = 0;
};