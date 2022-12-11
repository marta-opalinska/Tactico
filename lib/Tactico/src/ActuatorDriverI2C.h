// #pragma once
// #include <Interfaces/IActuatorDriver.h>

// #include <string>

// #include "HardwareLayer.h"

// // /**
// //  * @class ActuatorDriverI2C
// //  * @brief Class that stores information and methods for Actuator Driver
// //  * controlled using GPI pin
// //  * @implements IActuatorDriver
// //  * @param m_GPIO_pin GPIO pin of the assigned Actuator
// //  */
// class ActuatorDriverI2C : public IActuatorDriver {
//  protected:
//   int m_GPIO_pin;
//   void sendCommand();

//  public:
//   explicit ActuatorDriverI2C(int GPIO_pin);
//   ActuatorDriverI2C() = delete;
//   ~ActuatorDriverI2C() = default;
//   void initDriver();
//   void startActuator();
//   void stopActuator();
//   int getDriverPin();
//   void setDriverPin(int new_GPIO);
//   // play(PatternPWM pattern);
//   // void playInterval(int time);
// };
