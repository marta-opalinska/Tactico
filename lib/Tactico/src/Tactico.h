/** Copyright 2022 <Marta Opalinska> **/

/**
 * @brief Header file containing all header files from Tactico library
 *
 */
#pragma once
#include <Interfaces/IActuator.h>
#include <Interfaces/IActuatorDriver.h>
#include <Interfaces/IPattern.h>

#include <string>

#include "Action.h"
#include "ActuatorDriverDRV2605LEVM.h"
#include "ActuatorDriverGPIO.h"
#include "ActuatorDriverI2C.h"
#include "ActuatorERM.h"
#include "ActuatorLRA.h"
#include "Arduino.h"
#include "HapticDevice.h"
#include "HardwareLayer.h"
#include "PatternDRV2605L.h"
#include "PatternPWM.h"

/**
 * Needs for NRF52840 - min and max are ovewritten by Arduino library which
 * does not work with std library.
 */
// #undef min
// #undef max
