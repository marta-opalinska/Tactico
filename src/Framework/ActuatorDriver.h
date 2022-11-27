#pragma once
#include "HardwareLayer.h"

class ActuatorDriver

{
protected:
	int m_GPIO_pin;
	void initGPIO();
	void setHighGPIO();
	void setLowGPIO();
public:
	ActuatorDriver() = delete;
	ActuatorDriver(int GPIO_pin);
	~ActuatorDriver() = default;
	void startActuator();
	void stopActuator();
	void editGPIO(int new_GPIO);
	//play(Pattern pattern);
	//void playInterval(int time);
};
