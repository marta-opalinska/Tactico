# Tactico Framework
Tactico is a **haptics framework for embedded devices**. It supports multiple embedded platforms and actuators types.

## Table of Contents
1. Introduction - Introduction covering supported devices
2. Framework Architecture - Framework architecture and classes
3. Code examples - Examples of code usage

# Introduction

**Tactico** is a hardware independent C++  framework for **haptic device setup and control**. It can be used with different types of actuators. Currently the framework  supports LRA and ERM motors, but the modular architecture makes a new hardware integration easy. The control module can be wired or wireless depending on your preference. 

## Currently Supported Hardware

**Actuators**: Linear Resonant Actuator (LRA), Eccentric Rotating Mass (ERM)

**Tested Boards**: Arduino Nano 33 BLE, nRF52840

**Actuator’s Drivers**: DRV2605LEVM-MD, GPIO Driver thorugh Pulse-Width modulation(PWM)

# Bofore you start

Remember that the platform is **hardware agnostic** so there are some function that you as a user need to implement in order for the framework to work correctly.

Functions to implement are placed in **Tactico\src\HardwareLayer.cpp**:

- void i2c_begin()
- void i2c_write_reg(int address, int reg, int data)
- void i2c_write(int address, int reg)
void i2c_endTransmission()
- int i2c_read(int address, int reg, int numberBytes)

# Framework Architecture

![image info](./documentation/class_diagram_with_categories.png)
*Fig.1. A detailed view of the framework architecture.*

The detailed code documentation can be found in ***documentation\html\index.html***. In there you will find all classes with their methords and fields thoroughly explained. 

## Classes

As you could see on the above diagram there are multiple classes involved in the framework. Now we will go through all of them one by one.

### Actuator

![image info](./documentation/actuator_class.png)
*Fig.2. An example of an actuator alongside the infomration from the datasheet that will be needed for the implementation.*

**Actuator** class is the center point of the framework - it can be consider as a digital twin of the physical actuator. All the most important properties of an actuator need to be defined in the object of this class - **type** (LRA, ERM etc.), **rated voltage**, **peak voltage**, **resonant frequency** (for LRA) and an **Actuator Driver** instance that controls it.  

Currently two types of Actuators can be created - **ActuatorERM** and **ActuatorLRA**. They share most of the properties but they also have some specific ones. It is important to check which actuator you use so that the Actuator Driver is compatable with it (the driver can work differently depending on the actuator type).

### Actuator Driver

![image info](./documentation/driver_class.png)
*Fig.3. Currently supported drivers.*

**Actuator Driver** class defines the way in which the motor is performing a haptic effect. Currently there are user can choose from two available drivers - simple GPIO driver and driver on DRV2605LEVM-MD.

**GPIO Driver**
This is the type of a simple driver where the 

**Hardware Layer**

it ties the software with physical devices. 
### Pattern & Step

![image info](./documentation/pattern_step_class.png)
*Fig.4. Haptic Pattern and Step classes.*


PWM Pattern and DRV2605L pattern type

**Step**

Indivitudual activation of the actuator or wait command.

### Action

**Action**
Combines steps

### Haptic Device
You can combine all the above classes into one device. In that way you can control all the actuators and action at the same time.


# Code examples  
## Basic
### Creating an Actuator Driver

All the Drivers, Actuators, Patterns and Action instances are created with the use of **shared pointer**. In that way it is easier to manage them as they are passed to various functions in the runtime. 

- GPIO Driver

``` cpp

// pin that is connected to the actuator and supports Pulse Width-Modulation
int driverPinGPIO = 2;
// GPIO Driver - uses PMW patterns
std::shared_ptr<ActuatorDriverGPIO> driver_1 = 
    std::make_shared<ActuatorDriverGPIO>(driverPinGPIO);
```
- I2C Driver - DRV2605LEVM-MD
``` cpp
// DRV2605L evaluation board contains multiple DRV2605L drivers.
// Therefore the driver ID need to be specified.
int driverID = 0;
int driverGoPin = 12;

// DRV2605L Driver - communicated through I2C and uses DRV2605L effect library pattern
std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_2 =
    std::make_shared<ActuatorDriverDRV2605LEVM>(driverID, driverGoPin);
```

### Assiging an Actuator

- ERM Actuator
``` cpp
std::shared_ptr<ActuatorERM> actuator_1 =
    std::make_shared<ActuatorERM>(driver_1, 2, 3);

```
- LRA Actuator
``` cpp
std::shared_ptr<ActuatorLRA> actuator_2 =
    std::make_shared<ActuatorLRA>(driver_2, 2.5, 2.7, 100, "myLRA");
```

### Assiging a Pattern

- PWM Pattern
``` cpp
function test() {
  console.log("notice the blank line before this function?");
}
```
- DRV2605L Pattern (based on Texas Intruments Effect Library)
``` cpp
function test() {
  console.log("notice the blank line before this function?");
}
```
### Creating an action Step
- Actuator Step
``` cpp
function test() {
  console.log("notice the blank line before this function?");
}
```
- Wait Step
``` cpp
function test() {
  console.log("notice the blank line before this function?");
}
```

### Creating an Action


### Creating a Haptic Device

# Useful Links
 
- [Platformio for VS](https://docs.platformio.org/en/latest/integration/ide/visualstudio.html)

``` cpp
function test() {
  console.log("notice the blank line before this function?");
}
```