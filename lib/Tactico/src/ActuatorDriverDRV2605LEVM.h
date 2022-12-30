/** Copyright 2022 <Marta Opalinska> **/
#pragma once
#include <Interfaces/IActuatorDriver.h>

#include <memory>
#include <string>
#include <vector>

#include "ActuatorDriverI2C.h"
#include "HardwareLayer.h"
#include "PatternDRV2605L.h"
#include "DRV2605L_REG.h"

struct I2CCommands;
class PatternDRV2605L;

class ActuatorDriverDRV2605LEVM : public IActuatorDriver {
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
  // explicit ActuatorDriverDRV2605LEVM(int address);
  // explicit ActuatorDriverDRV2605LEVM(int goPin);
  explicit ActuatorDriverDRV2605LEVM(std::vector<I2CCommands> initialCommands);
  ActuatorDriverDRV2605LEVM(std::vector<I2CCommands> initialCommands,
                            int goPin);
  ActuatorDriverDRV2605LEVM(int goPin, int driverID);
  ActuatorDriverDRV2605LEVM(std::vector<I2CCommands> initialCommands,
                            std::vector<I2CCommands> preStartCommands);
  ActuatorDriverDRV2605LEVM(std::vector<I2CCommands> initialCommands,
                            std::vector<I2CCommands> preStartCommands,
                            int goPin);
  ActuatorDriverDRV2605LEVM() = delete;
  ~ActuatorDriverDRV2605LEVM() = default;
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
