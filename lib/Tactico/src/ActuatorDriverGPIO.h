#pragma once
#include <Interfaces/IActuatorDriver.h>
#include "HardwareLayer.h"

class ActuatorDriverGPIO : public IActuatorDriver
{
protected:
	int m_GPIO_pin;
	void setHighGPIO();
	void setLowGPIO();

public:
	ActuatorDriverGPIO() = delete;
	ActuatorDriverGPIO(int GPIO_pin);
	~ActuatorDriverGPIO() = default;
	void initDriver();
	void startActuator();
	void stopActuator();
	void editDriver(int new_GPIO);
	// play(PatternPWM pattern);
	// void playInterval(int time);
};
