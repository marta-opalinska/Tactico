#pragma once


#include <string>

#include <Wire.h>
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
void waitFor(int miliseconds);

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

// COMMANDS NECCESSARY FOR GPIO CONNECTION
void setPinStatusTactico(const int pinNumber, int pinStatus);

/**
 * @brief Implements hardware pin mode setting
 *
 * @param pinNumber pin number
 * @param pinModeStatus pin status
 */
void setPinModeTactico(const int pinNumber, int pinModeStatus);

// COMMANDS NECESSAY FOR I2C CONNECTION

/**
 * @brief Enables the I2C hardware

 *
 */
void i2c_begin();

/**
 * @brief Disables the I2C hardware
 *
 */
void i2c_end();

/**
 * @brief Initiate an I2C write operation, array of char.
 *
 * @param address the 7 bit I2C slave address
 * @param registerAddress address of the register you wish to access
 * @param data array of characters
 */
void i2c_write(int address, int registerAddress, int data);

/**
 * @brief Initiate a read operation of a specific number of bytes staring from
 * register address
 *
 * @param address the 7 bit I2C slave address
 * @param registerAddress starting register address to read data from
 * @param numberBytes the number of bytes to be read
 */
void i2c_read(int address, int registerAddress, int numberBytes);
