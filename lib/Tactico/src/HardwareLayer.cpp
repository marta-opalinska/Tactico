#include "HardwareLayer.h"


void waitForMiliseconds(int miliseconds){
    delay(miliseconds);
    std::string s = "Waiting for ";
    s.append(std::to_string(miliseconds));
    s.append("\n");
    printTactico(s);
    
}
void printTactico(const std::string s){
    Serial.print(s.c_str());
};

void setPinStatusTactico(const int pinNumber, int pinStatus){
    digitalWrite(pinNumber, pinStatus);
};

void setPinModeTactico(const int pinNumber, int pinModeStatus){
    pinMode(pinNumber, pinModeStatus);
};
