#include "Arduino.h"
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