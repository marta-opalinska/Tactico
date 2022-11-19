#include "Framework/HapticDevice.h"

HapticDevice::HapticDevice(std::vector<Actuator *> actuatorsList)
{
    this->m_actuatorsList = actuatorsList;
}

HapticDevice::HapticDevice(Actuator *signleActuator)
{
    this->m_actuatorsList.push_back(signleActuator);
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
void HapticDevice::removeActuator(int actuatorIndex)
{
    this->m_actuatorsList.erase(this->m_actuatorsList.begin() + actuatorIndex);
};

// Remove based on actuator name
void HapticDevice::removeActuator(std::string name)
{
    int i = 0;
    for (auto &ac : this->m_actuatorsList)
    {
        if (ac->name == name)
        {
            this->removeActuator(i);
        }
        i++;
    }
};

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
