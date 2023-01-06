/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IActuatorDriver.h>

#include <memory>
#include <string>
#include <vector>

#include "HardwareLayer.h"
#include "PatternDRV2605L.h"

/**
 * @brief I2C Command structure
 * @param address I2C device address
 * @param registerAddress register address
 * @param data data to send
 *
 */
typedef struct I2CCommands{
  int address;
  int registerAddress;
  int data;
} ;

class PatternDRV2605L;

/**
 * @class ActuatorDriverI2C
 * @brief  Class that stores configuration and methods for actuator driver
 * controlled through I2C
 * @implements IActuatorDriver
 *=
 */
class ActuatorDriverI2C : public IActuatorDriver {
 protected:
  /**
   * Flag checking if I2C was previously initialised
   */
  static bool m_I2C_Initialised;

  /**
   * I2C driver address
   */
  int m_address;

  /**
   * GPIO "go" pin for the driver
   */
  int m_goPin;

 public:
  ActuatorDriverI2C();
  ~ActuatorDriverI2C() = default;

  /**
   * @brief Initiate I2C bus.
   *
   */
  void initI2CBus();

  /**
   * @brief Initiate the driver.
   *
   */
  void init();

  /**
   * @brief Play the pattern supported by the driver.
   *
   * @param pattern pattern to play
   * @return true
   * @return false
   */
  virtual bool play(std::shared_ptr<IPattern> pattern) = 0;

  /**
   * @brief Test the motor vibration.
   *
   */
  virtual void test() = 0;

  /**
   * @brief Read a specific register.
   *
   * @param reg register to read
   * @return int
   */
  int readRegister(int reg);

  /**
   * @brief Write to a specific register
   *
   * @param reg register to write
   * @param data data to write
   */
  void writeRegister(int reg, int data);

  /**
   * @brief Set the I2C address
   *
   * @param address new I2C address
   */
  void setAddress(int address);

  /**
   * @brief Get the "go" GPIO pin
   *
   * @return int
   */
  int getGoPin();

  /**
   * @brief Need to be implemented by the implementation class.
   *
   */
  virtual void resetConfiguration() = 0;

  /**
   * @brief Get the ActuatorDriverType of the object
   *
   * @return ActuatorDriverType
   */
  ActuatorDriverType getType();
};
