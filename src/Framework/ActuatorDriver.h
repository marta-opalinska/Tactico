#pragma once

class ActuatorDriver

{
protected:
	int GPIO_pin;
	void initGPIO(int gpio);
	void setHighGPIO(int gpio);
	void setLowGPIO(int gpio);
public:
	ActuatorDriver() = delete;
	ActuatorDriver(int GPIO_pin);
	~ActuatorDriver() = default;
	void startActuator();
	void stopActuator();
	//play(Pattern pattern);
	//void playInterval(int time);
};
