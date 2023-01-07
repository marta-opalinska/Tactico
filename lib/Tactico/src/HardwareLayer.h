/** Copyright 2022 <Marta Opalinska> **/

/**
 * @brief This file need to be implemented by the user.
 * 
 */

#pragma once
// clang-format off
// Format need to be turned off - Arduino library need to be compiled as the last one 
// Arduino min and max function provides errors for NRF5280 chipset.
#include <Wire.h>

#include <string>

#include <Arduino.h>
#undef min
#undef max

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

//**************** COMMANDS NECCESSARY FOR GPIO CONNECTION

/**
 * @brief Implements hardware pin status setting LOW/HIGH
 *
 * @param pinNumber pin number
 * @param pinStatus expected pin status
 */
void setPinStatusTactico(const int pinNumber, int pinStatus);

/**
 * @brief Implements hardware pin mode setting - INPUT/OUTPUT
 *
 * @param pinNumber pin number
 * @param pinModeStatus pin status
 */
void setPinModeTactico(const int pinNumber, int pinModeStatus);

//**************** COMMANDS NECESSAY FOR I2C CONNECTION

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
void i2c_write_reg(int address, int registerAddress, int data);

/**
 * @brief Initiate an I2C transmission ending process.
 */
void i2c_endTransmission();

/**
 * @brief Initiate a read operation of a specific number of bytes staring
 * from register address
 *
 * @param address the 7 bit I2C slave address
 * @param registerAddress starting register address to read data from
 * @param numberBytes the number of bytes to be read
 */
int i2c_read(int address, int reg, int numberBytes);
