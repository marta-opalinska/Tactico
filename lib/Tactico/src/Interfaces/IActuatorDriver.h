#pragma once
#include "HardwareLayer.h"
#include <Interfaces/IWaveform.h>
#include <memory>

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

  virtual void init() = 0;
  /**
   * @brief Sends signal to the assigned interface to start it.
   *
   */

  virtual void play() = 0;
  /**
   * @brief Sends signal to the assigned interface object to stop it.
   *
   */

  virtual void stop() = 0;

  // /**
  //  * @brief Sends signal to play a specific pattern
  //  * 
  //  * @param pattern pattern to play
  //  */
  // virtual void play(std::shared_ptr<IWaveform> pattern) = 0;
};
