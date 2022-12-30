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

class ActuatorDriverDRV2605LEVM : public ActuatorDriverI2C {
 protected:
  bool m_usesDevBoard;
  int m_driverID;
  ActuatorType m_actuatorType;

  void initDRV2505L();
  void setWaveform(int slot, int w);
  void connectToMotor();
  void wait_for_motor_available();
  bool setupLRA(float ratedVoltage, float overdriveVoltage, int frequency);
  bool setupERM(float ratedVoltage, float overdriveVoltage);

 public:
  ActuatorDriverDRV2605LEVM(int driverID, int goPin);
  ActuatorDriverDRV2605LEVM() = delete;
  ~ActuatorDriverDRV2605LEVM() = default;
  void init();
  bool play(std::shared_ptr<IPattern> pattern);
  bool playInOrder(std::shared_ptr<PatternDRV2605L> pattern, int orderNumber);
  bool config(ActuatorType type, float ratedVoltage, float overdriveVoltage,
              int frequency = 300);
  ActuatorDriverType getType();
};
