#include "Arduino.h"
// Tactico framework imports
#include "Framework/Tactico.h"

// #include <iostream>
// #include "Framework/ActuatorDriver.h"
// #include "Framework/Actuator.h"
// #include <string.h>
// #include <string>

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT); // set pin as output
}

void loop()
{
	// digitalWrite(LED_BUILTIN, HIGH);  // set the LED on
	// delay(1000);               // wait for a second
	// digitalWrite(LED_BUILTIN, LOW);   // set the LED off
	// delay(1000);  // wait for a second

	ActuatorDriver d(8);
	std::string s = "ac_1";
	Actuator ac(d);
	Actuator ac_2(d, s);
	Actuator ac_3(d);
	d.editGPIO(10);
	std::vector<Actuator *> rightHandActuators = {&ac_2, &ac_3};
	HapticDevice right_hand(rightHandActuators);
	right_hand.startActuators();
	delay(500);
	right_hand.stopActuators();
	delay(500);
	right_hand.addActuator(&ac);
	right_hand.startActuators();
	delay(500);
	right_hand.stopActuators();
	delay(500);
	// cout << "Hello CMake." << endl;
	// cout << ac.name << endl;
	// cout << ac_2.name << endl;
	// cout << ac_3.name << endl;
}