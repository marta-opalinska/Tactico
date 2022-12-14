/** Copyright 2022 <Marta Opalinska> **/
#include "ActuatorDriverDRV2605LEVM.h"

#ifndef bit(b)
#define bit(b) (1UL << (b))
#endif

ActuatorDriverDRV2605LEVM::ActuatorDriverDRV2605LEVM(int driverID, int goPin)
    : m_driverID(driverID) {
  this->m_goPin = goPin;
  this->m_type = eDRV2505L_EVBOARD;
  this->m_address = DRV2605_ADDR;
  this->m_needsPreconfigration = true;
  setPinModeTactico(this->m_goPin, TACTICO_OUTPUT);
  this->init();
}

void ActuatorDriverDRV2605LEVM::init() {
  this->initI2CBus();

  // Enabling communication with servo 1-8
  i2c_write_reg(TCA9554_ADDR, CONF_IO_REG, 0xFF);

  // Activating all servos - That way it is not necessarly to keep track of
  // all the servos that need to be activate and mistakenly distctivate some of
  // them
  i2c_write_reg(TCA9554_ADDR, OUT_CHANNEL_REG, 0xFF);
  this->initDRV2605L();
}

void ActuatorDriverDRV2605LEVM::initDRV2605L() {
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

  // setting external trigger
  this->writeRegister(DRV2605_REG_MODE, DRV2605_MODE_EXTTRIGEDGE);
  // resetting waveform
  resetSequence();
}

bool ActuatorDriverDRV2605LEVM::setWaveform(int slotNumber,
                                            std::shared_ptr<IPattern> pattern) {
  if (slotNumber <= MAX_WAVEFORMS) {
    if (pattern->getType() == eDRV2505L) {
      this->connectToMotor();
      wait_for_motor_available();
      auto DRV2605LPattern(std::static_pointer_cast<PatternDRV2605L>(pattern));
      this->writeRegister(DRV2605_REG_WAVESEQ1 + slotNumber,
                          DRV2605LPattern->m_patternIndex);
      return true;
    } else {
      printTactico(
          "Invalid argument - ActuatorDriverDRV2605LEVM does not support this "
          "type of Pattern \n");
    }
    return false;
  }
  printTactico(
      "Invalid slot number! Max number of waveforms per driver is "
      "7.");
  return false;
}

bool ActuatorDriverDRV2605LEVM::setWait(int slotNumber, int milliseconds) {
  if (slotNumber <= MAX_WAVEFORMS) {
    this->connectToMotor();
    wait_for_motor_available();
    // the wait time need to be setup in 7 bits - therefore the register value
    // is need to be capped at 127 (MAX_WAIT_TIME_PER_SLOT)
    if (milliseconds / 10 > MAX_WAIT_TIME_PER_SLOT) {
      printTactico("WARNING: Wait time for the actuator DRV2605L driver id ");
      printTactico(std::to_string(m_driverID));
      printTactico(" needed to be capped at 1270ms!\n");
    }

    int milisecondsCapped = static_cast<int>(
        static_cast<int>(milliseconds * WAIT_BETWEEN_EFFECTS_MULTIPLIER) %
        MAX_WAIT_TIME_PER_SLOT);
    int timeToSend = WAIT_EFFECT_MSB + milisecondsCapped;
    this->writeRegister(DRV2605_REG_WAVESEQ1 + slotNumber, timeToSend);
    return true;
  }
  printTactico(
      "Invalid slot number! Max number of waveforms per driver is "
      "7.");
  return false;
}

bool ActuatorDriverDRV2605LEVM::play(std::shared_ptr<IPattern> pattern) {
  if (!this->setWaveform(0, pattern)) {
    return false;
  }
  go();
  resetSequence();
  return true;
}

void ActuatorDriverDRV2605LEVM::test() {
  std::shared_ptr<PatternDRV2605L> testPattern =
      std::make_shared<PatternDRV2605L>(BUZZ_1_100);
  this->setWaveform(0, testPattern);
  this->setWait(1, 300);
  this->setWaveform(2, testPattern);
  this->setWait(3, 300);
  go();
  resetSequence();
}

void ActuatorDriverDRV2605LEVM::go() {
  setPinStatusTactico(this->m_goPin, 1);
  waitFor(100);
  setPinStatusTactico(this->m_goPin, 0);
  while (this->readRegister(0x0C)) {
  }
}

void ActuatorDriverDRV2605LEVM::resetSequence() {
  this->connectToMotor();
  wait_for_motor_available();
  for (int i = 0; i < MAX_WAVEFORMS; i++) {
    this->writeRegister(DRV2605_REG_WAVESEQ1 + i, 0);
  }
}

void ActuatorDriverDRV2605LEVM::connectToMotor() {
  int motor_bit = bit(this->m_driverID);
  i2c_write(TCA9548_ADDR, motor_bit);
}

void ActuatorDriverDRV2605LEVM::wait_for_motor_available() {
  // if (this->readRegister(0x0C)) {
  //   this->writeRegister(DRV2605_REG_GO, 0);
  // }
  while (this->readRegister(0x0C)) {
  }
  return;
}

ActuatorDriverType ActuatorDriverDRV2605LEVM::getType() { return this->m_type; }

bool ActuatorDriverDRV2605LEVM::config(ActuatorType type, float ratedVoltage,
                                       float overdriveVoltage, int frequency) {
  switch (type) {
    case ActuatorType::eLRA: {
      setupLRA(ratedVoltage, overdriveVoltage, frequency);
      break;
    }
    case ActuatorType::eERM: {
      setupERM(ratedVoltage, overdriveVoltage);
      break;
    }
    default:
      printTactico("ActuatorDriverDRV2605LEVM: Actuator Type not supported.\n");
      return false;
  }

  return true;
}

void ActuatorDriverDRV2605LEVM::resetPreRunConfiguration() { this->resetSequence(); }

bool ActuatorDriverDRV2605LEVM::setupLRA(float ratedVoltage,
                                         float overdriveVoltage,
                                         int frequency) {
  this->connectToMotor();
  this->writeRegister(DRV2605_REG_FEEDBACK,
                      this->readRegister(DRV2605_REG_FEEDBACK) | 0x80);
  // library type selection - only one LRA library available
  this->writeRegister(DRV2605_REG_LIBRARY, 0x06);
  // calculating rated voltage register based on the datasheet with
  // default sample time value of 300 us
  float voltage_abs =
      ratedVoltage * std::sqrt(1 - (4 * SAMPLE_TIME + 0.0003) * frequency);
  int ratedVoltageReg = static_cast<int>((voltage_abs * 255) / 5.28);
  // setting rated voltage
  this->writeRegister(DRV2605_REG_RATEDV, ratedVoltageReg);

  // calculating overdrive voltage clamp
  int overdriveClamp = static_cast<int>((overdriveVoltage * 255) / 5.6);
  // setting max voltage
  this->writeRegister(DRV2605_REG_CLAMPV, overdriveClamp);
  return true;
}
bool ActuatorDriverDRV2605LEVM::setupERM(float ratedVoltage,
                                         float overdriveVoltage) {
  this->connectToMotor();
  this->writeRegister(DRV2605_REG_FEEDBACK,
                      this->readRegister(DRV2605_REG_FEEDBACK) & 0x7F);
  /** simplified library type selection - different categories depending on
   the actuator voltage rating more info can be found in DRV2605L datasheet
   (p.16) **/
  int libraryNumber = 1;
  if (ratedVoltage < 3.0 && overdriveVoltage < 3.0) {
    libraryNumber = 2;
  } else if (ratedVoltage < 3.2 && overdriveVoltage < 3.2) {
    libraryNumber = 3;
  } else {
    libraryNumber = 7;
  }
  this->writeRegister(DRV2605_REG_LIBRARY, libraryNumber);
  // CLOSE LOOP setup
  // registers set accordng to the driver DRV2605 datasheet
  int ratedVoltageReg = static_cast<int>((ratedVoltage * 255) / 5.36);
  // setting rated voltage
  this->writeRegister(DRV2605_REG_RATEDV, ratedVoltageReg);
  // setting max voltage with default drive time, blanking time and
  // IdissTime
  float voltagePeak =
      overdriveVoltage *
      ((DRIVE_TIME + IDISS_TIME + BLANKING_TIME) / (DRIVE_TIME - 0.0003));
  int overdriveClamp = static_cast<int>((voltagePeak * 255) / 5.44);
  this->writeRegister(DRV2605_REG_CLAMPV, overdriveClamp);
  return true;
}
