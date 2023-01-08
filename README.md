# Tactico Framework
Tactico is a **haptics framework for embedded devices**. It supports multiple embedded platforms and actuator types.

## Table of Contents

- [Tactico Framework](#tactico-framework)
  - [Table of Contents](#table-of-contents)
- [Introduction](#introduction)
- [Currently Supported Hardware](#currently-supported-hardware)
- [Before you start](#before-you-start)
- [Getting Started](#getting-started)
- [Framework Architecture](#framework-architecture)
  - [Actuator Class](#actuator-class)
    - [Creating An Actuator](#creating-an-actuator)
  - [Actuator Driver Class](#actuator-driver-class)
    - [Creating An Actuator Driver](#creating-an-actuator-driver)
  - [Pattern \& Step Classes](#pattern--step-classes)
    - [Pattern](#pattern)
      - [Creating a Pattern](#creating-a-pattern)
    - [Step](#step)
      - [Creating a Step](#creating-a-step)
  - [Action Class](#action-class)
      - [Creating An Action](#creating-an-action)
  - [Haptic Device Class](#haptic-device-class)
      - [Creating And Using A Haptic Device](#creating-and-using-a-haptic-device)
  - [Controller Class](#controller-class)
- [Useful Links](#useful-links)

# Introduction

**Tactico** is a hardware independent C++ open-sourced framework for **haptic device setup and control**. It is suitable for different types of actuators and actuator drivers. Currently, the framework supports LRA and ERM motors, but the modular architecture makes new hardware integration easy. The control module can be wired or wireless, depending on your preference. 

# Currently Supported Hardware

**Actuators**: Linear Resonant Actuator (LRA), Eccentric Rotating Mass (ERM)

**Tested Boards**: Arduino Nano 33 BLE, nRF52840

**Actuator’s Drivers**: DRV2605LEVM-MD, GPIO Driver thorugh Pulse-Width modulation(PWM)

# Before you start

Remember that the platform is **hardware agnostic**, so there are some functions that you, as a user, need to implement for the framework to work correctly.

Functions to implement can be found in **Tactico\src\HardwareLayer.cpp**:

- void **waitFor**(int miliseconds);
- void **printTactico**(const std::string s);
- void **setPinStatusTactico**(const int pinNumber, int pinStatus);
- void **setPinModeTactico**(const int pinNumber, int pinModeStatus);
- void **i2c_begin**();
- void **i2c_write_reg**(int address, int reg, int data);
- void **i2c_endTransmission**();
- int **i2c_read**(int address, int reg, int numberBytes);

All these commands tie the framework code to the utilised physical hardware.

# Getting Started 

An example main file can be found in *src/main.cpp*.

# Framework Architecture

The detailed code documentation can be viewed [here](https://marta-opalinska.github.io/Tactico/html/index.html). All classes with their methods and fields are thoroughly explained in there.

Fig.1 presents numerous classes that are involved in the framework. In the following sections you will find a general explanation of each of them.

![image info](./docs/class_diagram_with_categories.png)
*Fig.1. A detailed view of the framework architecture.*

## Actuator Class

**Actuator** class is the centre point of the framework - it can be considered a digital twin of the physical actuator. All the most important properties of an actuator need to be defined in the object of this class - **type** (LRA, ERM etc.), **rated voltage**, **peak voltage**, **resonant frequency** (for LRA) and an **Actuator Driver** instance, that controls it.  

Currently, two types of Actuators can be created - **ActuatorERM** and **ActuatorLRA**. They share most of the properties but also have some specific ones. It is essential to check which actuator you use so that the Actuator Driver is compatible with it (the driver can work differently depending on the actuator type).

The framework supports testing the connected actuators by calling the **test()** command. It will send a single vibration test to the motor. It is highly recommended to test the hardware before processing with further framework implementation. 

![image info](./docs/actuator_class.png)
*Fig.2. An example of an actuator alongside the information from the datasheet that will be needed for the implementation.*

### Creating An Actuator

Before creating an Actuator object you need to have a Actuator Driver object created - to do that follow [this example](#creating-an-actuator-driver)

- ERM Actuator
``` cpp

#include "Tactico.h"

// ...

// ----------------- ERM WITH GPIO DRIVER
// the standard DC voltage for the actuator
float ratedVoltage_ERM_1 = 2.0;
// the maximum allowable DC voltage
float overdriveVoltage_ERM_1 = 2.5;
// optional - custom name will be prited alongside logs refering to the
// actuator
std::string customName_ERM_1 = "myERM_1";

std::shared_ptr<ActuatorERM> actuator_ERM_1 = std::make_shared<ActuatorERM>(
    driver_GPIO, ratedVoltage_ERM_1, overdriveVoltage_ERM_1, customName_ERM_1);

// It is recommended to test the connection with the actuator before
// developing the code further - the actuator should vibrate
actuator_ERM_1->test();

// ----------------- ERM WITH DRV2605LEVM DRIVER
float ratedVoltage_ERM_2 = 2.0;
float overdriveVoltage_ERM_2 = 2.5;

std::string customName_ERM_2 = "myERM_2";

std::shared_ptr<ActuatorERM> actuator_ERM_2 = std::make_shared<ActuatorERM>(
    driver_DRV2605L_1, ratedVoltage_ERM_2, overdriveVoltage_ERM_2, customName_ERM_2);

// It is recommended to test the connection with the actuator before
// developing the code further - the actuator should vibrate
actuator_ERM_2->test();
```
- LRA Actuator
``` cpp
#include "Tactico.h"

// ...

// the standard DC voltage for the actuator
float ratedVoltage_LRA = 2.0;
// the maximum allowable DC voltage
float overdriveVoltage_LRA = 2.5;
// LRA actuator resonant frequency (can be found in the datasheet)
int resonantFrequency_LRA = 170;
// optional - custom name will be prited alongside logs refering to the
// actuator
std::string customName_LRA = "myLRA_1";

std::shared_ptr<ActuatorLRA> actuator_LRA = std::make_shared<ActuatorLRA>(
    driver_DRV2605L_2, ratedVoltage_LRA, overdriveVoltage_LRA,
    resonantFrequency_LRA, customName_LRA);

// It is recommended to test the connection with the actuator before
// developing the code further - the actuator should vibrate
actuator_LRA->test();

```

## Actuator Driver Class

**Actuator Driver** class defines the way in which the motor performs a haptic effect. Currently, users can choose from two available drivers - a simple GPIO driver and a driver from the DRV2605LEVM-MD board.

**GPIO Driver**

GPIO Driver is a simple driver with the motor connected to a single GPIO output and controlled using **Pulse Width Modulation Pattern**. In order to use this driver, the following functions from **HardwareLayer.cpp** need to be implemented: waitFor, printTactico, setPinStatusTactico and setPinModeTactico from (more about it [here](#before-you-start)). 

**DRV2605LEVM-MD**

The DRV2605LEVM-MD driver **requires I2C communication** - connection of three pins (CLC, SDA and GND), as well as the implementation of I2C related commands in **HardwareLayer.cpp** file (more about it in [Before you start section](#before-you-start)). In this particular class, a fourth hardware connection is needed - GPIO **"GO" pin** that will trigger the haptic effect. 

**ActuatorDriverDRV2605LEVM** uses the DRV2605L list of registers (specified in **DRV2605L_REG.h**) and the list of haptic effects (**DRV2605L_EFFECTS.h**). 

It **needs pre-run configuration** before any haptic effect is played! The configuration allows the user to store an effect sequence in the physical DRV2605L driver's memory and play it when the "GO" pin is triggered (the "GO" pin needs to go HIGH). 

Therefore, when this type of actuator is used as a part of the **Action** class instance, the **configure() function needs to be called before play()** (or configureAndPlay(), which triggers the configuration and then the play of an Action). The advantage of the pre-run configuration is that Action Steps can be triggered in parallel (more about it in [Action Class section](#action)). 

![image info](./docs/driver_class.png)
*Fig.3. Currently supported drivers.*

### Creating An Actuator Driver

All the Drivers, Actuators, Patterns and Action instances are created with the use of **shared pointer**. In that way it is easier to manage them as they are passed to various functions in the runtime. 

- GPIO Driver

``` cpp
#include "Tactico.h"

// ...

// pin that is connected to the actuator and supports Pulse Width-Modulation
int driverPinGPIO = 22;
// GPIO Driver - uses PMW patterns
std::shared_ptr<ActuatorDriverGPIO> driver_GPIO =
    std::make_shared<ActuatorDriverGPIO>(driverPinGPIO);
```

- I2C Driver - DRV2605LEVM-MD
``` cpp

#include "Tactico.h"

// ...

// DRV2605L evaluation board contains multiple DRV2605L drivers.
// Therefore the driver ID need to be specified.
int driverID_1 = 0;
// the pin connected to DRV2605LEVM-MD board that triggers the haptic effects
int driverGoPin = 12;

// DRV2605L Driver - communicated through I2C
//                    uses DRV2605L effect library pattern
std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_DRV2605L_1 =
    std::make_shared<ActuatorDriverDRV2605LEVM>(driverID_1, driverGoPin);

// Another driver from DRV2605LEVM board - this time with driver ID 1
int driverID_2 = 1;

std::shared_ptr<ActuatorDriverDRV2605LEVM> driver_DRV2605L_2 =
    std::make_shared<ActuatorDriverDRV2605LEVM>(driverID_2, driverGoPin);
```

## Pattern & Step Classes

### Pattern

Some patterns are only suitable for a specific actuator or an actuator driver (see Tab.1).

| Actuator/Driver | Actuator Driver DRV2605LEVM | Actuator Driver GPIO |
| --------------- | --------------------------- | -------------------- |
| LRA             | Pattern DRV2605L            | -                    |
| ERM             | Pattern DRV2605L            | Pattern PWM          |

*Tab. 1. Table representing what available pattern can be used with a specific actuator-driver combination.*

Two available patterns represent entirely different approaches. **DRV2605L Pattern** is simply holding an index of the pattern that will be played from the library, while the PWM pattern is more complex. **PWM pattern** is created manually by the user with a ModulationPWM structure. The modulation is defined by the duration of the pulse and if it is a binary 1 or 0 pulse.

![image info](./docs/modulation_explanation.png)
*Fig.5. The explanation of ModulationPWM structure.*


The most significant advantage of the Pattern class is that it can be assigned to many actuators simultaneously. The pattern instance is **created once**, and all of the actuators of a suitable type can use it. 


![image info](./docs/pattern_class.png)
*Fig.4. Pattern class.*

#### Creating a Pattern

- Pulse Width Mudulation (PWM) Pattern 

``` cpp
#include "Tactico.h"

// ...

/*
    Custom Pulse Width Mudulation that specifies
    duration in miliseconds (in this example 100ms and 50ms)
    and status (1 = true = ON or 0 = false = OFF)
*/
std::vector<ModulationPWM> modulationPWM_1 = {
    {100, true}, {50, false}, {100, true},
    {50, false}, {100, true}, {50, false},
};

std::shared_ptr<PatternPWM> pattern_PWM_1 =
    std::make_shared<PatternPWM>(modulationPWM_1);

```

- DRV2605L Pattern (using in-build library of haptic effects)

``` cpp
#include "Tactico.h"

// ...


/*
All in-build effect available for the DRV2605L can be found in
DRV2605L_EFFECTS.h file
*/
std::shared_ptr<PatternDRV2605L> pattern_DRV2605L_CLICK =
    std::make_shared<PatternDRV2605L>(STRONG_CLICK_100);

std::shared_ptr<PatternDRV2605L> pattern_DRV2605L_BUZZ =
    std::make_shared<PatternDRV2605L>(STRONG_BUZZ_100);
```

### Step

**Step** can be considered an individual activation of the actuator or a Wait command. Steps are a data class that only stores information about the objects involved in the step, and to play them, they need to be combined into the Action - more about it in the [Action Class section](#action).

The Step can be configured to be **played in parallel** with other steps. This functionality is available only for actuators that drivers allow pre-run configuration (e.g. DRV2605L but **NOT** DriverGPIO). That means that the software will store the activation sequence in the physical driver's memory and simply triggers it with a GO pin. The value of driver's **m_needsPreconfigration** field indicates if the driver can be configered priour the run. The Step parallelisation property needs to be set during the Step creation by assigning *true* to **isParallel** field. 

More about Steps sequences can be found in [Action Class section](#action).

![image info](./docs/step_class.png)
*Fig.5. Step class.*

#### Creating a Step

- Wait Step (pauses all actuators for a specific time duration)
``` cpp
#include "Tactico.h"

// ...

// duration of the wait in miliseconds - 200ms
int waitTime_200 = 200;

std::shared_ptr<WaitStep> s_wait_200 =
    std::make_shared<WaitStep>(waitTime_200);

// duration of the wait in miliseconds - 400ms
int waitTime_400 = 200;

std::shared_ptr<WaitStep> s_wait_400 =
    std::make_shared<WaitStep>(waitTime_400);
```


- Non-parallel Actuator Steps - step will be performed one after another
``` cpp
#include "Tactico.h"

// ...

// step that combines actuator_ERM_1 with pattern pattern_PWM_1 -
// This step is not parallel. Step's constructor field 'isParallel' is FALSE
// by default. No need to specify it.
std::shared_ptr<ActuatorStep> s_ERM_1_PWM_1 =
    std::make_shared<ActuatorStep>(actuator_ERM_1, pattern_PWM_1);

// step that combines s_ERM_2_DRV2605L_BUZZ with pattern_DRV2605L_CLICK
// This step is not parallel.
std::shared_ptr<ActuatorStep> s_ERM_2_DRV2605L_BUZZ =
    std::make_shared<ActuatorStep>(actuator_ERM_2, pattern_DRV2605L_BUZZ);
```
- Parallel Actuator Steps - steps will be performed in parallel (simutanously) to other parallel steps.

``` cpp
#include "Tactico.h"

// ...
bool isParallel_yes = true;
// step that combines actuator_ERM_2 with pattern_DRV2605L_CLICK - this step
// is run in parallel
std::shared_ptr<ActuatorStep> s_ERM_2_DRV2605L_CLICK =
    std::make_shared<ActuatorStep>(actuator_ERM_2, pattern_DRV2605L_CLICK,
                                    isParallel_yes);

std::shared_ptr<ActuatorStep> s_LRA_DRV2605L_CLICK =
    std::make_shared<ActuatorStep>(actuator_LRA, pattern_DRV2605L_CLICK,
                                    isParallel_yes);
```

## Action Class

The **Action** class combines previously explained Steps into a sequence of haptic effects. All available actuator types and patterns can be combined to create a new haptic experience. 

As mentioned in [Actuator Driver Class section](#actuator-driver-class), **some drivers require pre-run configuration** to play a pattern. Therefore it is necessary for each Action to either call:

- **configure()** and **play()** consecutively

OR

- **configureAndPlay()**, which will configure all involved actuators and immediately play the Action

The Action can involve some of the steps played in parallel. The step parallelisation property can be assigned only during the Step object creation. However, it is limited to the specific motor drivers that allow pre-run configuration(e.g. works with DRV2605L, but **NOT** with GPIO driver). 

To keep the Action clean, it is recommended to call **resetPreviousConfiguration()** each time after the action is played (unless it will be repeated). In that way, pre-run memory will be reset, and non of the previously played actuator will be accidentally triggered by the same GO pin as assigned to the other actuators (which is the case when using the DRV2605LEVM board). This function is not automatically activated if the Action is set up once and used multiple times in a row. 

An Action can become a part of a Haptic Device. 

![image info](./docs/action_class.png)
*Fig.6. Example of creating parallel and non-parallel actions. The step parallelisation property needs to be assigned when the step is created.*

#### Creating An Action

``` cpp
#include "Tactico.h"

// ...

  std::shared_ptr<Action> a_forward = std::make_shared<Action>();

  a_forward->setSteps({s_ERM_1_PWM_1, s_wait_200, s_ERM_2_DRV2605L_BUZZ});

  std::shared_ptr<Action> a_forward_and_right = std::make_shared<Action>();

  a_forward_and_right->addStep(s_ERM_1_PWM_1);
  a_forward_and_right->addStep(s_wait_400);
  a_forward_and_right->addStep(s_LRA_DRV2605L_CLICK_PARALLEL);
  a_forward_and_right->addStep(s_ERM_2_DRV2605L_CLICK_PARALLEL);

```

## Haptic Device Class

You can combine all the above classes into one **Haptic Device** entity. In that way, you can control all the actuators and actions simultaneously. 

As previously explained in the Action section, it is recommended to reset the previous pre-run configuration if not used subsequently. When using Haptic Device, you can make sure that all actuators have clean pre-run configuration by using **resetActuatorsPreRunConfiguration()**.

![Haptic Device Class Image](./docs/haptic_device_class.png)
*Fig.7. A graphical representation of a haptic device with Actuators and Actions assigned.*


#### Creating And Using A Haptic Device

- Create
``` cpp
#include "Tactico.h"

// ...

  HapticDevice haptic_band({actuator_ERM_1, actuator_ERM_2, actuator_LRA});
  haptic_band.addAction(a_forward, "go-forward");

  haptic_band.addAction(a_forward_and_right, "go-forward-and-right");

  haptic_band.testActuators();


```
- Use
``` cpp

// ...

haptic_band.configureAction("go-forward");
delay(2000);
haptic_band.playAction("go-forward");
haptic_band.resetActuatorsPreRunConfiguration();
delay(1000);
haptic_band.configureAndPlayAction("go-forward-and-right");

```

## Controller Class

The framework supports the creation of a custom external controller to control the Haptic Device behaviour. Currently, no controller is implemented, but the framework's flexibility allows it to be easily added. 

# Useful Links
 
- [Platformio for VS](https://docs.platformio.org/en/latest/integration/ide/visualstudio.html)

- [DRV2605L Documentation](https://www.ti.com/lit/ds/symlink/drv2605l.pdf?ts=1672415752878)