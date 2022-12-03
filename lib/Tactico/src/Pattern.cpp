#include "Pattern.h"


PatternPWM::PatternPWM(std::vector<Modulation> switching_modulation)
: m_switching_modulation(switching_modulation){}

void PatternPWM::setModulation(std::vector<Modulation> switching_modulation)
{
    this->m_switching_modulation = switching_modulation;
}

void PatternPWM::play(std::shared_ptr<IActuator> ac)
{
    for (auto m : this->m_switching_modulation){
        // if()
        if (m.isOn){
            ac->start();
        }
        else{
            ac->stop();
        }
        waitForMiliseconds(m.duration);
    }
}

// void Pattern::stop(std::shared_ptr<Actuator> ac)
// {
// }

// students[x]=y;