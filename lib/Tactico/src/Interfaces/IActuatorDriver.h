/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <memory>

#include "HardwareLayer.h"
#include "Interfaces/IPattern.h"

/**
 * @brief Enum of the possible actuator's driver types. It is used for driver
 * specific methods.
 *
 */
enum ActuatorDriverType { eGPIO, eI2C, eDRV2505L_EVBOARD };

/**
 * @interface IActuatorDriver
 * @brief Interface for actuator driver - the interface is implemented by the
 * ActuatorDriverGPIO, ActuatorDriverI2C and ActuatorDriverDRV2605LEVM classes
 *
 */
class IActuatorDriver {
 protected:
  /**
   * actuator's driver type based on enum ActuatorDriverType
   */
  ActuatorDriverType m_type;

 public:
  /**
   * defines if the driver needs to be preconfigured before the action can be
   * played e.g. by sending the pattern before hitting GO.
   */
  bool m_needsPreconfigration;
  /**
   * @brief Starts initialisation of the driver
   *
   */
  virtual void init() = 0;

  /**
   * @brief Play a pattern
   *
   * @param pattern shared pointer to the implementation of a Pattern instance
   * @return true
   * @return false
   */
  virtual bool play(std::shared_ptr<IPattern> pattern) = 0;

  /**
   * @brief Driver testing.
   *
   */
  virtual void test() = 0;

  virtual void resetPreRunConfiguration() = 0;

  /**
   * @brief Get the driver's type
   *
   * @return ActuatorDriverType
   */
  virtual ActuatorDriverType getType() = 0;
};
