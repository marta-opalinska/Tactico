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
		ActuatorDriver driver_4(17);
		Serial.print("Iniatiation of drivers done. \n");
		std::string s = "ac_1";
		Actuator ac_1(driver_1,s);
		driver_1.editGPIO(10);


		Actuator ac_2(driver_2);
		Actuator ac_3(driver_3);
	
		// std::vector<Actuator *> rightHandActuators = {&ac_1, &ac_2};
		// HapticDevice right_hand(rightHandActuators);
		// Serial.print("Starting RIGHT HAND. \n");
		// right_hand.addActuator(&ac_3);
		// right_hand.startActuators();
		// delay(500);
		// Serial.print("Stoping RIGHT HAND. \n");
		// right_hand.stopActuators();
		// ac_3.setDriver(driver_4);
		// delay(500);
		// Serial.print("Starting RIGHT HAND. \n");
		// right_hand.startActuators();
		// delay(500);
		// Serial.print("Stoping RIGHT HAND. \n");
		// right_hand.stopActuators();

		// delay(500);

		// right_hand.removeActuator("ac_1");
		// right_hand.removeActuator(&ac_2);
		// Serial.print("Starting RIGHT HAND. \n");
		// right_hand.startActuators();
		// delay(500);		
		// Serial.print("Stoping RIGHT HAND. \n");
		// right_hand.stopActuators();

		// right_hand.addActuator(&ac_1);
		// // right_hand.swapActuator(&ac_3, &ac_2);
		// Serial.print("Before swap:  \n");
		// Serial.print("Starting RIGHT HAND. \n");
		// right_hand.startActuators();
		// delay(500);		
		// Serial.print("Stoping RIGHT HAND. \n");
		// right_hand.stopActuators();

		// Action left;
		// left.addStep(ac_1, true);
		// left.addWait(500);
		// left.addStep(ac_2, true);
		// left.addWait(500);
		// left.addStep(ac_1, false);
		// left.addStep(ac_2, false);
		
		// left.play();

		std::vector<Modulation> mod_1{{200,true}, {200, false}, {100, true}, {100, false}};
		Pattern p_1(mod_1);
		std::shared_ptr<Actuator> ac_1_ptr = std::make_shared<Actuator>(ac_1);
		p_1.play(ac_1_ptr);

		setupDone = true;
	}
	Serial.print("------------------------------------- \n");

	Serial.print("Loop ... \n");
	delay(15000);
}