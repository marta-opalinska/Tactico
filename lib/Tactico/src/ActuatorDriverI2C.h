/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuatorDriver.h>

#include <memory>
#include <string>
#include <vector>

#include "HardwareLayer.h"
#include "PatternDRV2605L.h"

/**
 * @class ActuatorDriverI2C
 * @brief Class that stores information and methods for Actuator Driver
 * controlled using GPI pin
 * @implements IActuatorDriver
 * @param m_GPIO_pin GPIO pin of the assigned Actuator
 */

struct I2CCommands {
  int address;
  int registerAddress;
  int data;
};

class PatternDRV2605L;

class ActuatorDriverI2C : public IActuatorDriver {
 protected:
  static bool m_I2C_Initialised;
  bool m_usesGoPinFlag;
  bool m_usesStartCommands;
  bool m_usesDevBoard;
  std::vector<I2CCommands> m_initialCommands;
  int m_goPin;
  int m_driverID;
  ActuatorType m_actuatorType;
  void initDRV2505L();
  void init(std::vector<I2CCommands> initialCommands);
  // int calculateRatedVoltageReg();
  // int calculateODClampReg();
  void writeRegister(int reg, int data);
  int readRegister(int reg);
  void setWaveform(int slot, int w);
  void connectToMotor();
  void wait_for_motor_available();
  bool setupLRA(float ratedVoltage, float overdriveVoltage, int frequency);
  bool setupERM(float ratedVoltage, float overdriveVoltage);

 public:
  // explicit ActuatorDriverI2C(int address);
  // explicit ActuatorDriverI2C(int goPin);
  explicit ActuatorDriverI2C(std::vector<I2CCommands> initialCommands);
  ActuatorDriverI2C(std::vector<I2CCommands> initialCommands, int goPin);
  ActuatorDriverI2C(int goPin, int driverID);
  ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
                    std::vector<I2CCommands> preStartCommands);
  ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
                    std::vector<I2CCommands> preStartCommands, int goPin);
  ActuatorDriverI2C() = delete;
  ~ActuatorDriverI2C() = default;
  void init();
  bool play(std::shared_ptr<IPattern> pattern);
  bool playInOrder(std::shared_ptr<PatternDRV2605L> pattern, int orderNumber);
  void sendCommand(int address, int sendRegister, int data);
  void setAddress(int address);
  bool config(ActuatorType type, float ratedVoltage, float overdriveVoltage,
              int frequency = 300);
  DriverType getType();
  // play(PatternPWM pattern);
  // void playInterval(int time);
};
