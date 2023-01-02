/** Copyright 2022 <Marta Opalinska> **/

#pragma once
#include <Interfaces/IPattern.h>

#include <memory>

#include "HardwareLayer.h"

/**
 * @brief Interface for a external controller class.
 *
 */
class IController {
 public:
  /**
   * @brief Connect to the controller.
   *
   */
  virtual void connect() = 0;

  /**
   * @brief Send the current haptic device configuration.
   *
   */
  virtual void sendConfiguration() = 0;

  /**
   * @brief Triggered by the incomming command from the cotroller.
   *
   */
  virtual void onCommand() = 0;
};
