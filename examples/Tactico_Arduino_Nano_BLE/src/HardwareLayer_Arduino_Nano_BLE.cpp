/** Copyright 2022 <Marta Opalinska> **/

#include <Arduino.h>
#include <Wire.h>

#include <string>

#include "HardwareLayer.h"
#undef min
#undef max

void waitFor(int miliseconds) { delay(miliseconds); }

void printTactico(const std::string s) { Serial.print(s.c_str()); }

void setPinStatusTactico(const int pinNumber, int pinStatus) {
  digitalWrite(pinNumber, pinStatus);
}

void setPinModeTactico(const int pinNumber, int pinModeStatus) {
  pinMode(pinNumber, pinModeStatus);
}

void i2c_begin() { Wire.begin(); }

void i2c_write_reg(int address, int reg, int data) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void i2c_write(int address, int reg) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
}

void i2c_endTransmission() { Wire.endTransmission(); }

int i2c_read(int address, int reg, int numberBytes) {
  int reading = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(reg, numberBytes);

  if (numberBytes <= Wire.available()) {
    reading = Wire.read();  // receive high byte (overwrites previous reading)

    reading = reading << 8;  // shift high byte to be high 8 bits

    reading |= Wire.read();  // receive low byte as lower 8 bits
  }
  Wire.endTransmission();
  return reading;
}
