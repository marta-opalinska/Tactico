#include "Arduino.h"
// Tactico framework imports
#include "Framework/Tactico.h"

// #include <iostream>
// #include "Framework/ActuatorDriver.h"
// #include "Framework/Actuator.h"
// #include <string.h>
// #include <string>
	
int setupDone;

void setup()
{
	Serial.begin(9600);
	setupDone = false;

	// pinMode(LED_BUILTIN, OUTPUT); // set pin as output
	

	Serial.print("------------------------------------- \n");
}

void loop()
{
	delay(1000);
	if (!setupDone){
		Serial.print("------------------------------------- \n");
		Serial.print("Initiating Drivers... \n");
		ActuatorDriver driver_1(8);
		ActuatorDriver driver_2(12);
		ActuatorDriver driver_3(15);
		Serial.print("Iniatiation of drivers done. \n");
		std::string s = "ac_1";
		Actuator ac(driver_1);
		ac.start();
		delay(500);
		ac.stop();
		driver_1.editGPIO(10);
		ac.start();
		delay(500);
		ac.stop();
		setupDone = true;
		
		


		// Actuator ac_2(driver_2, s);
		// Actuator ac_3(driver_3);
	
		// std::vector<Actuator *> rightHandActuators = {&ac_2, &ac_3};
		// HapticDevice right_hand(rightHandActuators);
		// right_hand.startActuators();
		// delay(500);
		// right_hand.stopActuators();
		// delay(500);
		// right_hand.addActuator(&ac);
		// right_hand.startActuators();
		// delay(500);
		// right_hand.stopActuators();
	}
	Serial.print("------------------------------------- \n");

	// digitalWrite(LED_BUILTIN, HIGH);  // set the LED on
	// delay(1000);               // wait for a second
	// digitalWrite(LED_BUILTIN, LOW);   // set the LED off
	// delay(1000);  // wait for a second
	Serial.print("Loop ... \n");
	delay(15000);
	// cout << "Hello CMake." << endl;
	// cout << ac.name << endl;
	// cout << ac_2.name << endl;
	// cout << ac_3.name << endl;
}