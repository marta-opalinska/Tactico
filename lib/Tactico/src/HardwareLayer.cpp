#include "HardwareLayer.h"

void waitFor(int miliseconds) {
  delay(miliseconds);
  // std::string s = "Waiting for ";
  // s.append(std::to_string(miliseconds));
  // s.append("\n");
  // printTactico(s);
}

void printTactico(const std::string s) { Serial.print(s.c_str()); }

void setPinStatusTactico(const int pinNumber, int pinStatus) {
  digitalWrite(pinNumber, pinStatus);
}

void setPinModeTactico(const int pinNumber, int pinModeStatus) {
  pinMode(pinNumber, pinModeStatus);
}

void i2c_begin() {
  Wire.begin();

  // // Enabling communication with servo 1-5
  // Wire.beginTransmission(TCA9554_adr);
  // Wire.write(CONF_IO_REG);
  // Wire.write(0xFF);
  // Wire.endTransmission();

  // // setting servo 1-5 to active
  // Wire.beginTransmission(TCA9554_adr);
  // Wire.write(OUT_CHANNEL_REG);
  // Wire.write(0xFF);
  // Wire.endTransmission();

  // // for some reason TCA9548 configuration only works when 0-3 motors
  // // are configured separately from 4-7 motors
  // Wire.beginTransmission(TCA9548_adr);
  // Wire.write(0x0F);
  // Wire.endTransmission();
}

void i2c_write_reg(int address, int reg, int data) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void i2c_write(int address, int reg) {
  Wire.beginTransmission(address);
  Wire.write(reg);
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