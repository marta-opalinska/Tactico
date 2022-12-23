#pragma once
// clang-format off
// Format need to be turned off - Arduino library need to be compiled as the last one 
// Arduino min and max function provides errors for NRF5280 chipset.
#include <Wire.h>

#include <string>

#include <Arduino.h>
#undef min
#undef max


#define DRV2605L_REG_RATED_VOLTAGE 0x16
#define DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE 0x17
#define DRV2605L_REG_CONTROL_3 0x1D
#define DRV2605L_REG_LIBRARY_SELECTION 0x03
#define DRV2605L_MODE_SELECTION 0x01
#define BOLD_TEXT String("\033[1m")
#define RESET_TEXT String("\033[0m")

#define TCA9548_adr 0x70
#define TCA9554_adr 0x20
#define DRV2605L_adr 0x5A
#define CONF_IO_REG 0x03
#define OUT_CHANNEL_REG 0x01
// clang-format on

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
void i2c_write_reg(int address, int registerAddress, int data);

/**
 * @brief Initiate an I2C write operation, array of char. When the transmission
 * is done the i2c_endTransmission() function need to be called.
 *
 * @param address the 7 bit I2C slave address
 * @param registerAddress address of the register you wish to access
 */

void i2c_write(int address, int reg);

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
