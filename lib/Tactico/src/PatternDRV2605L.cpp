/** Copyright 2022 <Marta Opalinska> **/

#include "PatternDRV2605L.h"

#include <string>

#include "DRV2605L_EFFECTS.h"

PatternDRV2605L::PatternDRV2605L(int patternIndex,
                                 int patternDuration /*= AVERAGE_PATTERN_TIME*/)
    : m_patternIndex(patternIndex), m_patternDuration(patternDuration) {
  this->m_type = eDRV2505L;
}

void PatternDRV2605L::init() {}

std::string PatternDRV2605L::patternToString() {
  std::string s = "DRV2605LPattern: ";
  s.append(std::to_string(m_patternIndex));
  s.append("\n");
  return s;
}

int PatternDRV2605L::getPatternDuration() { return m_patternDuration; }

PatternType PatternDRV2605L::getType() { return this->m_type; }

// void PatternDRV2605L::stop(std::shared_ptr<Actuator> ac)
// {
// }
// students[x]=y;
