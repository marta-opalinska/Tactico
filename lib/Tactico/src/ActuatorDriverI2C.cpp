#include "ActuatorDriverI2C.h"

bool ActuatorDriverI2C::m_I2C_Initialised = false;

ActuatorDriverI2C::ActuatorDriverI2C(int goPin, int driverID)
    : m_goPin(goPin), m_driverID(driverID) {
  this->m_usesGoPinFlag = true;
  setPinModeTactico(this->m_goPin, OUTPUT);
  this->init();
}

ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands)
    : m_initialCommands(initialCommands) {
  this->init(initialCommands);
}

ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
                                     int goPin)
    : m_initialCommands(initialCommands), m_goPin(goPin) {
  setPinModeTactico(this->m_goPin, OUTPUT);
  this->init(initialCommands);
}
ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
                                     std::vector<I2CCommands> preStartCommands)
    : m_initialCommands(initialCommands) {
  this->init(initialCommands);
}
ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
                                     std::vector<I2CCommands> preStartCommands,
                                     int goPin)
    : m_initialCommands(initialCommands), m_goPin(goPin) {
  setPinModeTactico(this->m_goPin, OUTPUT);
  this->init(initialCommands);
}

void ActuatorDriverI2C::init(std::vector<I2CCommands> initialCommands) {
  if (!this->m_I2C_Initialised) {
    printTactico("I2C init....");
    i2c_begin();
    printTactico("I2c Init done.");
  }

  this->m_type = I2C;
  // TODO loop on each command!!!
  //  initDRV2505();
}

void ActuatorDriverI2C::init() {
  // if (!this->m_I2C_Initialised) {
  i2c_begin();
  // }
  this->m_type = I2C;

  // Enabling communication with servo 1-8
  i2c_write_reg(TCA9554_ADDR, CONF_IO_REG, 0xFF);

  // Activating all servos - in that way it is not necessarly to keep track of
  // all the servos that need to be activate and mistakenly distctivate some of
  // them
  i2c_write_reg(TCA9554_ADDR, OUT_CHANNEL_REG, 0xFF);

  // int activeMotor = pow(2, this->m_driverID);
  // // activate the communication with the servo
  // i2c_write(TCA9548_ADDR, activeMotor);
  // i2c_endTransmission();

  this->initDRV2505L();
}

void ActuatorDriverI2C::initDRV2505L() {
  this->connectToMotor();
  // commands for driver innitiation
  this->writeRegister(DRV2605_REG_MODE, 0x00);  // out of standby

  this->writeRegister(DRV2605_REG_RTPIN, 0x00);  // no real-time-playback

  this->writeRegister(DRV2605_REG_WAVESEQ1, 1);  // strong click
  this->writeRegister(DRV2605_REG_WAVESEQ2, 0);  // end sequence

  this->writeRegister(DRV2605_REG_OVERDRIVE, 0);  // no overdrive

  this->writeRegister(DRV2605_REG_SUSTAINPOS, 0);
  this->writeRegister(DRV2605_REG_SUSTAINNEG, 0);
  this->writeRegister(DRV2605_REG_BREAK, 0);
  this->writeRegister(DRV2605_REG_AUDIOMAX, 0x64);

  // turn off N_ERM_LRA
  this->writeRegister(DRV2605_REG_FEEDBACK,
                      this->readRegister(DRV2605_REG_FEEDBACK) & 0x7F);

  // turn off open loop for both LRA & ERM - uses close loop
  this->writeRegister(DRV2605_REG_CONTROL3, 0x81);

  // setting open-loop control drive
  this->writeRegister(DRV2605_REG_CONTROL3, 0x81);
  this->writeRegister(DRV2605_REG_LIBRARY, 0x06);
  // setting external trigger
  this->writeRegister(DRV2605_REG_MODE, DRV2605_MODE_EXTTRIGEDGE);
  // resetting waveform
  this->setWaveform(0, 0);

  this->sendType(LRA);

  this->sendVoltages(LRA, 3, 3.3, 300);
}

void ActuatorDriverI2C::sendType(ActuatorType type) {
  this->m_actuatorType = type;

  if (this->m_actuatorType == LRA) {
    this->writeRegister(DRV2605_REG_FEEDBACK,
                        this->readRegister(DRV2605_REG_FEEDBACK) | 0x80);
  }

  if (this->m_actuatorType == ERM) {
    this->writeRegister(DRV2605_REG_FEEDBACK,
                        this->readRegister(DRV2605_REG_FEEDBACK) & 0x7F);
  }
}
void ActuatorDriverI2C::sendVoltages(ActuatorType type, float ratedVoltage,
                                     float overdriveVoltage, int frequency = 300) {
  // setting rated voltage
  this->writeRegister(DRV2605_REG_RATEDV, 0x68);
  // setting max voltage
  this->writeRegister(DRV2605_REG_CLAMPV, 0x92);
}

void ActuatorDriverI2C::setWaveform(int slot, int w) {
  this->writeRegister(DRV2605_REG_WAVESEQ1 + slot, w);
}
void ActuatorDriverI2C::writeRegister(int reg, int data) {
  i2c_write_reg(DRV2605_ADDR, reg, data);
}

int ActuatorDriverI2C::readRegister(int reg) {
  return i2c_read(DRV2605_ADDR, reg, 1);
}

bool ActuatorDriverI2C::play(std::shared_ptr<IPattern> pattern) {
  // connect to motor
  printTactico("Play....");
  printTactico(std::to_string(this->m_driverID));
  this->connectToMotor();

  wait_for_motor_available();

  this->setWaveform(0, 48);
  this->setWaveform(1, WAIT_BETWEEN_EFFECTS);
  this->setWaveform(2, 48);
  this->setWaveform(3, WAIT_BETWEEN_EFFECTS);
  this->setWaveform(4, 48);
  this->setWaveform(5, WAIT_BETWEEN_EFFECTS);
  this->setWaveform(6, 0);  // end of waveforms

  this->m_goPin = 12;
  digitalWrite(m_goPin, HIGH);
  delay(250);
  digitalWrite(m_goPin, LOW);
  // wait for the actuator to finish
  while (this->readRegister(0x0C)) {
  };
  this->setWaveform(0, 0);
  return true;
}

void ActuatorDriverI2C::connectToMotor() {
  int motor_bit = bit(this->m_driverID);
  Wire.beginTransmission(TCA9548_ADDR);
  Wire.write(motor_bit);
  Wire.endTransmission();
}

void ActuatorDriverI2C::wait_for_motor_available() {
  if (this->readRegister(0x0C)) {
    this->writeRegister(DRV2605_REG_GO, 0);
  }
  while (this->readRegister(0x0C)) {
  };
  return;
}

void ActuatorDriverI2C::stop() {}
int ActuatorDriverI2C::getAddress() { return DRV2605_ADDR; }
void ActuatorDriverI2C::sendCommand(int address, int sendRegister, int data) {}
DriverType ActuatorDriverI2C::getType() { return this->m_type; }

bool ActuatorDriverI2C::config(ActuatorType type, float ratedVoltage,
                               float overdriveVoltage, int frequency) {
  this->sendType(type);
  this->sendVoltages(type, ratedVoltage, overdriveVoltage);
  return true;
}

// void ActuatorDriverI2C::setGPIOHigh() {
//   setPinStatusTactico(this->m_GPIO_pin, 1);
// }

// void ActuatorDriverI2C::setLowGPIO() {
//   setPinStatusTactico(this->m_GPIO_pin, 0);
// }

// void ActuatorDriverI2C::play() {
//   this->setGPIOHigh();
//   std::string s = "Actuator Driver START, GPIO ";
//   s.append(std::to_string(this->m_GPIO_pin));
//   s.append("\n");
//   printTactico(s);
// }

// void ActuatorDriverI2C::stop() {
//   this->setLowGPIO();
//   std::string s = "Actuator Driver STOP, GPIO ";
//   s.append(std::to_string(this->m_GPIO_pin));
//   s.append("\n");
//   printTactico(s);
// }
// void ActuatorDriverI2C::setPin(int new_GPIO) {
//   this->setLowGPIO();
//   this->m_GPIO_pin = new_GPIO;
//   this->init();
// }

// int ActuatorDriverI2C::getPin() {
//   return this->m_GPIO_pin;
// }

// void ActuatorDriverI2C::play(IPattern pattern){

// }
