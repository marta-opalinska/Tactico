/** Copyright 2022 <Marta Opalinska> **/
#pragma once
#include <Interfaces/IActuatorDriver.h>

#include <memory>
#include <string>
#include <vector>

#include "ActuatorDriverI2C.h"
#include "DRV2605L_REG.h"
#include "HardwareLayer.h"
#include "PatternDRV2605L.h"

struct I2CCommands;
class PatternDRV2605L;

class ActuatorDriverDRV2605LEVM : public ActuatorDriverI2C {
 protected:
  bool m_usesDevBoard;
  int m_driverID;
  ActuatorType m_actuatorType;

  void initDRV2505L();
  void connectToMotor();
  void wait_for_motor_available();
  bool setupLRA(float ratedVoltage, float overdriveVoltage, int frequency);
  bool setupERM(float ratedVoltage, float overdriveVoltage);

 public:
  ActuatorDriverDRV2605LEVM(int driverID, int goPin);
  ActuatorDriverDRV2605LEVM() = delete;
  ~ActuatorDriverDRV2605LEVM() = default;
  void init();
  void go();
  bool play(std::shared_ptr<IPattern> pattern);
  bool playInOrder(std::shared_ptr<PatternDRV2605L> pattern, int orderNumber);
  void test();
  bool config(ActuatorType type, float ratedVoltage, float overdriveVoltage,
              int frequency = 300);
  void resetSequence();
  bool setWaveform(int orderNumber, std::shared_ptr<IPattern> pattern);
  bool setWait(int orderNumber, int miliseconds);

  ActuatorDriverType getType();
};
