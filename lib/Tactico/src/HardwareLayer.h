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

/**
 * @brief Implements hardware wait/delay function
 *
 * @param miliseconds time of the wait
 */
void waitForMiliseconds(int miliseconds);

/**
 * @brief Implements hardware print function
 *
 * @param s string to print
 */
void printTactico(const std::string s);

/**
 * @brief Implements hardware pin status setting
 *
 * @param pinNumber pin number
 * @param pinStatus expected pin status
 */
void setPinStatusTactico(const int pinNumber, int pinStatus);

/**
 * @brief Implements hardware pin mode setting
 *
 * @param pinNumber pin number
 * @param pinModeStatus pin status
 */
void setPinModeTactico(const int pinNumber, int pinModeStatus);
