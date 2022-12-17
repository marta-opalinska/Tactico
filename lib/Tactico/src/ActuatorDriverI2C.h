#pragma once
#include <Interfaces/IActuatorDriver.h>

#include <string>
#include <vector>

#include "HardwareLayer.h"

// /**
//  * @class ActuatorDriverI2C
//  * @brief Class that stores information and methods for Actuator Driver
//  * controlled using GPI pin
//  * @implements IActuatorDriver
//  * @param m_GPIO_pin GPIO pin of the assigned Actuator
//  */

struct I2CCommands {
  int address;
  int registerAddress;
  int data;
};

class ActuatorDriverI2C : public IActuatorDriver {
 protected:
  int m_address;
  int m_goPin;
  static bool m_I2C_Initialised;
  bool m_usesGoPinFlag;
  bool m_usesStartCommands;
  std::vector<I2CCommands> m_initialCommands;

 public:
  explicit ActuatorDriverI2C(int address);
  ActuatorDriverI2C(int address, int goPin);
  ActuatorDriverI2C(int address, std::vector<I2CCommands> initialCommands);
  ActuatorDriverI2C(int address, std::vector<I2CCommands> initialCommands,
                    int goPin);
  ActuatorDriverI2C(int address, std::vector<I2CCommands> initialCommands,
                    std::vector<I2CCommands> preStartCommands);
  ActuatorDriverI2C(int address, std::vector<I2CCommands> initialCommands,
                    std::vector<I2CCommands> preStartCommands, int goPin);
  ActuatorDriverI2C() = delete;
  ~ActuatorDriverI2C() = default;
  void init();
  bool play(std::shared_ptr<IPattern> pattern);
  void stop();
  int getAddress();
  void sendCommand();
  void setAddress(int address);
  DriverType getType();
  // play(PatternPWM pattern);
  // void playInterval(int time);
};
