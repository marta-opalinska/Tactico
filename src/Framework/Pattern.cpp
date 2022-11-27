#include "Pattern.h"


Pattern::Pattern(std::vector<Modulation> switching_modulation)
: m_switching_modulation(switching_modulation){}

void Pattern::setModulation(std::vector<Modulation> switching_modulation)
{
    this->m_switching_modulation = switching_modulation;
}

void Pattern::play(std::shared_ptr<Actuator> ac)
{
    for (auto m : this->m_switching_modulation){
        // if()
        ac->start();
        waitForMiliseconds(m.duration);
    }
}

void Pattern::stop(std::shared_ptr<Actuator> ac)
{
}

// students[x]=y;