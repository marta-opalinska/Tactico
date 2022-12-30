#pragma once
#include <Interfaces/IPattern.h>

#include <memory>

#include "HardwareLayer.h"

/**
 * @interface IActuatorDriver
 * @brief Interface for actuator driver - the interface is implemented by the
 * ActuatorDriverGPIO class
 *
 */
enum DriverType { eGPIO, eI2C };

class IActuatorDriver {
 protected:
  DriverType m_type;

 public:
  /**
   * @param m_needsPreconfigration defines if the driver needs to be
   * preonfigured before the action can be played e.g. by sending the pattern
   * before hitting GO.
   *
   */
  bool m_needsPreconfigration;
  /**
   * @brief Starts initialisation of the driver
   *
   */
  virtual void init() = 0;

  /**
   * @brief Sends signal to the assigned interface to play a Pattern.
   *
   */

  virtual bool play(std::shared_ptr<IPattern> pattern) = 0;
  /**
   * @brief Sends signal to the assigned interface object to stop it.
   *
   */

  // virtual void stop() = 0;

  virtual DriverType getType() = 0;

  // /**
  //  * @brief Sends signal to play a specific pattern
  //  *
  //  * @param pattern pattern to play
  //  */
  // virtual void play(std::shared_ptr<IPattern> pattern) = 0;
};
