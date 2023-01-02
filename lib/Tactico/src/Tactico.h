/** Copyright 2022 <Marta Opalinska> **/

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

#undef min
#undef max
