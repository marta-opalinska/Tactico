// /** Copyright 2022 <Marta Opalinska> **/

// #include "ActuatorDriverI2C.h"

// bool ActuatorDriverI2C::m_I2C_Initialised = false;

// ActuatorDriverI2C::ActuatorDriverI2C(int goPin, int driverID)
//     : m_goPin(goPin), m_driverID(driverID) {
//   this->init();
//   this->m_usesGoPinFlag = true;
//   setPinModeTactico(this->m_goPin, OUTPUT);
//   this->m_needsPreconfigration = true;
// }

// ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands)
//     : m_initialCommands(initialCommands) {
//   this->init(initialCommands);
// }

// ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
//                                      int goPin)
//     : m_initialCommands(initialCommands), m_goPin(goPin) {
//   setPinModeTactico(this->m_goPin, OUTPUT);
//   this->init(initialCommands);
// }
// ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
//                                      std::vector<I2CCommands> preStartCommands)
//     : m_initialCommands(initialCommands) {
//   this->init(initialCommands);
// }
// ActuatorDriverI2C::ActuatorDriverI2C(std::vector<I2CCommands> initialCommands,
//                                      std::vector<I2CCommands> preStartCommands,
//                                      int goPin)
//     : m_initialCommands(initialCommands), m_goPin(goPin) {
//   setPinModeTactico(this->m_goPin, OUTPUT);
//   this->init(initialCommands);
// }

// void ActuatorDriverI2C::init(std::vector<I2CCommands> initialCommands) {
//   if (!this->m_I2C_Initialised) {
//     i2c_begin();
//     m_I2C_Initialised = true;
//   }

//   this->m_type = eI2C;
//   // TODO loop on each command!!!
//   //  initDRV2505();
// }

// void ActuatorDriverI2C::init() {
//   if (!this->m_I2C_Initialised) {
//     i2c_begin();
//   }
//   this->m_type = eI2C;

//   // Enabling communication with servo 1-8
//   i2c_write_reg(TCA9554_ADDR, CONF_IO_REG, 0xFF);

//   // Activating all servos - in that way it is not necessarly to keep track of
//   // all the servos that need to be activate and mistakenly distctivate some of
//   // them
//   i2c_write_reg(TCA9554_ADDR, OUT_CHANNEL_REG, 0xFF);
//   this->initDRV2505L();
// }

// void ActuatorDriverI2C::initDRV2505L() {
//   this->connectToMotor();

//   // commands for driver innitiation
//   this->writeRegister(DRV2605_REG_MODE, 0x00);  // out of standby

//   this->writeRegister(DRV2605_REG_RTPIN, 0x00);  // no real-time-playback

//   this->writeRegister(DRV2605_REG_WAVESEQ1, 1);  // strong click
//   this->writeRegister(DRV2605_REG_WAVESEQ2, 0);  // end sequence

//   this->writeRegister(DRV2605_REG_OVERDRIVE, 0);  // no overdrive

//   this->writeRegister(DRV2605_REG_SUSTAINPOS, 0);
//   this->writeRegister(DRV2605_REG_SUSTAINNEG, 0);
//   this->writeRegister(DRV2605_REG_BREAK, 0);
//   this->writeRegister(DRV2605_REG_AUDIOMAX, 0x64);

//   // turn off N_ERM_LRA
//   this->writeRegister(DRV2605_REG_FEEDBACK,
//                       this->readRegister(DRV2605_REG_FEEDBACK) & 0x7F);

//   // turn off open loop for both LRA & ERM - uses close loop
//   this->writeRegister(DRV2605_REG_CONTROL3, 0x81);

//   // setting open-loop control drive
//   this->writeRegister(DRV2605_REG_CONTROL3, 0x81);

//   // setting external trigger
//   this->writeRegister(DRV2605_REG_MODE, DRV2605_MODE_EXTTRIGEDGE);
//   // resetting waveform
//   this->setWaveform(0, 0);
// }

// void ActuatorDriverI2C::setWaveform(int slot, int w) {
//   this->writeRegister(DRV2605_REG_WAVESEQ1 + slot, w);
// }
// void ActuatorDriverI2C::writeRegister(int reg, int data) {
//   i2c_write_reg(DRV2605_ADDR, reg, data);
// }

// int ActuatorDriverI2C::readRegister(int reg) {
//   return i2c_read(DRV2605_ADDR, reg, 1);
// }

// bool ActuatorDriverI2C::playInOrder(std::shared_ptr<PatternDRV2605L> pattern,
//                                     int orderNumber) {
//   this->connectToMotor();
//   wait_for_motor_available();
//   this->setWaveform(orderNumber, pattern->m_patternIndex);
//   return true;
// }

// bool ActuatorDriverI2C::play(std::shared_ptr<IPattern> pattern) {
//   if (pattern->getType() == eDRV2505L) {
//     this->connectToMotor();
//     wait_for_motor_available();
//     // TODO setting pattern index!
//     auto DRV2605LPattern(std::static_pointer_cast<PatternDRV2605L>(pattern));
//     this->setWaveform(0, DRV2605LPattern->m_patternIndex);
//     this->setWaveform(1, WAIT_BETWEEN_EFFECTS);
//     this->setWaveform(2, 48);
//     this->setWaveform(3, WAIT_BETWEEN_EFFECTS);
//     this->setWaveform(4, 48);
//     this->setWaveform(5, WAIT_BETWEEN_EFFECTS);
//     this->setWaveform(6, 0);  // end of waveforms

//     this->m_goPin = 12;
//     digitalWrite(m_goPin, HIGH);
//     delay(250);
//     digitalWrite(m_goPin, LOW);
//     // wait for the actuator to finish
//     while (this->readRegister(0x0C)) {
//     }
//     this->setWaveform(0, 0);
//     return true;
//   } else {
//     printTactico(
//         "Invalid argument - ActuatorDriverI2C does not support this type of "
//         "Pattern");
//   }
//   return false;
// }

// void ActuatorDriverI2C::connectToMotor() {
//   int motor_bit = bit(this->m_driverID);
//   Wire.beginTransmission(TCA9548_ADDR);
//   Wire.write(motor_bit);
//   Wire.endTransmission();
// }

// void ActuatorDriverI2C::wait_for_motor_available() {
//   if (this->readRegister(0x0C)) {
//     this->writeRegister(DRV2605_REG_GO, 0);
//   }
//   while (this->readRegister(0x0C)) {
//   }
//   return;
// }
// void ActuatorDriverI2C::sendCommand(int address, int sendRegister, int data) {}
// DriverType ActuatorDriverI2C::getType() { return this->m_type; }

// bool ActuatorDriverI2C::config(ActuatorType type, float ratedVoltage,
//                                float overdriveVoltage, int frequency) {
//   switch (type) {
//     case ActuatorType::eLRA: {
//       setupLRA(ratedVoltage, overdriveVoltage, frequency);
//       break;
//     }
//     case ActuatorType::eERM: {
//       setupERM(ratedVoltage, overdriveVoltage);
//       break;
//     }
//     default:
//       printTactico("ActuatorDriverI2C: Actuator Type not supported.\n");
//       return false;
//   }
//   // this->sendType(type, ratedVoltage, overdriveVoltage);
//   // this->sendVoltages(type, ratedVoltage, overdriveVoltage);
//   return true;
// }

// bool ActuatorDriverI2C::setupLRA(float ratedVoltage, float overdriveVoltage,
//                                  int frequency) {
//   this->writeRegister(DRV2605_REG_FEEDBACK,
//                       this->readRegister(DRV2605_REG_FEEDBACK) | 0x80);
//   // library type selection - only one LRA library available
//   this->writeRegister(DRV2605_REG_LIBRARY, 0x06);
//   // CLOSE LOOP setup
//   this->writeRegister(DRV2605_REG_FEEDBACK,
//                       this->readRegister(DRV2605_REG_FEEDBACK) | 0x80);
//   // library type selection - only one LRA library available
//   this->writeRegister(DRV2605_REG_LIBRARY, 0x06);
//   // TODO
//   // calculating rated voltage register based on the datasheet with
//   // default sample time value of 300 us
//   float voltage_abs =
//       ratedVoltage * std::sqrt(1 - (4 * SAMPLE_TIME + 0.0003) * frequency);
//   int ratedVoltageReg = static_cast<int>((voltage_abs * 255) / 5.28);
//   // setting rated voltage
//   this->writeRegister(DRV2605_REG_RATEDV, ratedVoltageReg);
//   // calculating overdrive voltage clamp
//   int overdriveClamp = static_cast<int>((overdriveVoltage * 255) / 5.6);
//   // setting max voltage
//   this->writeRegister(DRV2605_REG_CLAMPV, overdriveClamp);
//   return true;
// }
// bool ActuatorDriverI2C::setupERM(float ratedVoltage, float overdriveVoltage) {
//   this->writeRegister(DRV2605_REG_FEEDBACK,
//                       this->readRegister(DRV2605_REG_FEEDBACK) & 0x7F);
//   /** simplified library type selection - different categories depending on
//    the actuator voltage rating more info can be found in DRV2605L datasheet
//    (p.16) **/
//   int libraryNumber = 1;
//   if (ratedVoltage < 3.0 && overdriveVoltage < 3.0) {
//     libraryNumber = 2;
//   } else if (ratedVoltage < 3.2 && overdriveVoltage < 3.2) {
//     libraryNumber = 3;
//   } else {
//     libraryNumber = 7;
//   }
//   this->writeRegister(DRV2605_REG_LIBRARY, libraryNumber);
//   // CLOSE LOOP setup
//   // registers set accordng to the driver DRV2605 datasheet
//   int ratedVoltageReg = static_cast<int>((ratedVoltage * 255) / 5.36);
//   // setting rated voltage
//   this->writeRegister(DRV2605_REG_RATEDV, ratedVoltageReg);
//   // setting max voltage with default drive time, blanking time and
//   // IdissTime
//   float voltagePeak =
//       overdriveVoltage *
//       ((DRIVE_TIME + IDISS_TIME + BLANKING_TIME) / (DRIVE_TIME - 0.0003));
//   int overdriveClamp = static_cast<int>((voltagePeak * 255) / 5.44);
//   this->writeRegister(DRV2605_REG_CLAMPV, overdriveClamp);
//   return true;
// }
