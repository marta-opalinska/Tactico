#pragma once
#include <string>
#include <Arduino.h>
#undef min
#undef max

// typedef enum PinStatusTactico
// {
//     LOW,
//     HIGH
// };

// typedef enum PinModeTactico
// {
//     INPUT = 0x0,
//     OUTPUT = 0x1
// };

void waitForMiliseconds(int miliseconds);
void printTactico(const std::string s);
void setPinStatusTactico(const int pinNumber, int pinStatus);
void setPinModeTactico(const int pinNumber, int pinModeStatus);
