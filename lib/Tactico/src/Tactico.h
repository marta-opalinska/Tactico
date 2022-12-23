

// Tactico_.h : Include file for standard system include files,
// or project specific include files.

#pragma once
// #include <iostream>

// #include <Interfaces/IActuator.h>
#include <Interfaces/IActuator.h>
#include <Interfaces/IActuatorDriver.h>
#include <Interfaces/IPattern.h>

#include <string>

#include "Action.h"
#include "ActuatorDriverGPIO.h"
#include "ActuatorDriverI2C.h"
#include "ActuatorERM.h"
#include "ActuatorLRA.h"
#include "Arduino.h"
#include "HapticDevice.h"
#include "PatternPWM.h"
#include "PatternDRV2605L.h"
#include "HardwareLayer.h"

#undef min
#undef max

// TODO: Reference additional headers your program requires here.
