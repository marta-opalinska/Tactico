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
  int m_address;
  int m_goPin;

 public:
  ActuatorDriverI2C();
  ~ActuatorDriverI2C() = default;
  void initI2CBus();
  void init();
  virtual bool play(std::shared_ptr<IPattern> pattern) = 0;
  virtual void test() = 0;
  int readRegister(int reg);
  void writeRegister(int reg, int data);
  void setAddress(int address);
  int getGoPin();
  ActuatorDriverType getType();
};
