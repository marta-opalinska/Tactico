#include "HapticDevice.h"
#include "Arduino.h"

int HapticDevice::nextID = 0;
const std::string HapticDevice::defaultName = "device_";

HapticDevice::HapticDevice(std::vector<Actuator *> actuatorsList,  const std::string & name /*=""*/)
    : m_actuatorsList(actuatorsList)
{
    this->id = ++nextID;
    if (name == ""){
        this->m_name = defaultName;
	    this->m_name.append(std::to_string(id));
    }
    else{this->m_name = name;}
}

HapticDevice::HapticDevice(Actuator *signleActuator,  const std::string & name /*=""*/)
{
    this->m_actuatorsList.push_back(signleActuator);
    this->id = ++nextID;
    if (name == ""){
        this->m_name = defaultName;
	    this->m_name.append(std::to_string(id));
    }
    else{this->m_name = name;}
}

void HapticDevice::renameDevice(const std::string & name)
    {
        this->m_name = name;
    }

void HapticDevice::addActuator(Actuator *actuator)
{
    this->m_actuatorsList.push_back(actuator);
};

void HapticDevice::addActuators(std::vector<Actuator *> actuatorsVector)
{
    for (auto ac : actuatorsVector)
    {
        this->addActuator(ac);
    }
};

void HapticDevice::removeActuator(Actuator *actuator)
{
    // v.erase(std::remove_if(v.begin(), v.end(), IsOdd), v.end());
    // The erase–remove idiom which is a common C++ technique
    this->m_actuatorsList.erase(std::remove(this->m_actuatorsList.begin(), this->m_actuatorsList.end(), actuator), this->m_actuatorsList.end());
};

// Index calculated from 0 an according to adding to the list
void HapticDevice::removeActuator(int actuatorPosition)
{
    this->m_actuatorsList.erase(this->m_actuatorsList.begin() + actuatorPosition);
};

// Remove based on actuator name
void HapticDevice::removeActuator( const std::string & name)
{
    int i = 0;
    for (auto &ac : this->m_actuatorsList)
    {
        if (ac->m_name == name)
        {
            this->removeActuator(i);
        }
        i++;
    }
};

// void HapticDevice::swapActuator(Actuator* oldActuator, Actuator* newActuator){
//     this->addActuator(newActuator);

//     int position = 0;
//     for (auto &ac : this->m_actuatorsList)
//     {
//         Serial.print(position);
//         if (ac == oldActuator)
//         {
//             Serial.print("FOUND \n");
//             break;
//         }
//         position++;
//     }

//     std::iter_swap(this->m_actuatorsList.begin() + position, this->m_actuatorsList.end());
// }

void HapticDevice::startActuators()
{
    for (auto &ac : m_actuatorsList)
    {
        ac->start();
    }
};

void HapticDevice::stopActuators()
{
    for (auto &ac : m_actuatorsList)
    {
        ac->stop();
    }
};