#pragma once
#include "HardwareLayer.h"

/**
 * @interface IActuatorDriver
 * @brief Interface for actuator driver - the interface is implemented by the
 * ActuatorDriverGPIO class
 *
 */
class IActuatorDriver {
 public:
  /**
   * @brief Starts initialisation of the driver
   *
   */

  virtual void initDriver() = 0;
  /**
   * @brief Sends signal to the assigned interface to start it.
   *
   */

  virtual void startActuator() = 0;
  /**
   * @brief Sends signal to the assigned interface object to stop it.
   *
   */

  virtual void stopActuator() = 0;
};
