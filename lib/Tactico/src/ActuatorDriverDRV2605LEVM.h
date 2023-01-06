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

#define MAX_WAIT_TIME_PER_SLOT 127

class PatternDRV2605L;

/**
 * @class ActuatorDriverDRV2605LEVM
 * @brief  Class that stores configuration and methods for DRV2605L evalution
 * board actuator's driver (controlled through I2C)
 * @details The driver can have up to 7 waveforms (or wait times) preconfigured
 * - each need to be assigned to a specific slot. The slots will be played when
 * "go" pin is triggered
 * @implements ActuatorDriverI2C
 *
 */

class ActuatorDriverDRV2605LEVM : public ActuatorDriverI2C {
 protected:
  /**
   * Unique driver ID
   */
  int m_driverID;
  /**
   * Type of actuator that the driver controlls
   */
  ActuatorType m_actuatorType;
  /**
   * @brief Initiate a DRV2605L driver
   *
   */
  void initDRV2605L();

  /**
   * @brief Conenct to the motor to start the communication.
   *
   */
  void connectToMotor();

  /**
   * @brief Wait till the motor stops performing previously send waveforms.
   *
   */
  void wait_for_motor_available();

  /**
   * @brief Setup for LRA motor types
   *
   * @param ratedVoltage actuator's rated voltage
   * @param overdriveVoltage actuator's peak voltag
   * @param frequency actuator's resonance frequency
   * @return true
   * @return false
   */
  bool setupLRA(float ratedVoltage, float overdriveVoltage, int frequency);

  /**
   * @brief Setup for ERM motor types
   *
   * @param ratedVoltage actuator's rated voltage
   * @param overdriveVoltage actuator's peak voltag
   * @return true
   * @return false
   */
  bool setupERM(float ratedVoltage, float overdriveVoltage);

 public:
  /**
   * @brief Construct a new Actuator Driver DRV2605LEVM
   *
   * @param driverID evaluation board driver number
   * @param goPin GPIO pin that starts the play
   */
  ActuatorDriverDRV2605LEVM(int driverID, int goPin);
  ActuatorDriverDRV2605LEVM() = delete;
  ~ActuatorDriverDRV2605LEVM() = default;

  /**
   * @brief Init the driver.
   *
   */
  void init();

  /**
   * @brief Trigger "go" pin - starts of the predefined action.
   *
   */
  void go();

  /**
   * @brief Play the pattern supported by the driver.
   *
   * @param pattern pattern to play
   * @return true
   * @return false
   */
  bool play(std::shared_ptr<IPattern> pattern);

  /**
   * @brief Test the motor vibration.
   *
   */
  void test();

  /**
   * @brief Send the configuration of the actuator to the driver.
   *
   * @param type actuator type
   * @param ratedVoltage actuator's rated voltage
   * @param overdriveVoltage actuator's peak voltag
   * @param frequency actuator's resonant frequency
   * @return true
   * @return false
   */
  bool config(ActuatorType type, float ratedVoltage, float overdriveVoltage,
              int frequency = 300);

  /**
   * @brief Reseting previously setup configuration for to play - the actuator
   * configuration will remain the same!.
   *
   */
  void resetConfiguration();

  /**
   * @brief Reset configured sequence of patterns.
   *
   */
  void resetSequence();

  /**
   * @brief Set the Waveform to the specific slot (sequence number).
   *
   * @param slotNumber waveform sequence slot number - the driver has max. 7
   * slots.
   * @param pattern pattern to play (needs to be supported by the driver)
   * @return true
   * @return false
   */
  bool setWaveform(int slotNumber, std::shared_ptr<IPattern> pattern);

  /**
   * @brief Set the Wait time to the specific slot (sequence number).
   *
   * @param slotNumber waveform sequence slot number - the driver has max. 7
   * slots.
   * @param miliseconds time to wait (in miliseconds)
   * @return true
   * @return false
   */
  bool setWait(int slotNumber, int miliseconds);

  /**
   * @brief Get the ActuatorDriverType of the object
   *
   * @return ActuatorDriverType
   */
  ActuatorDriverType getType();
};
