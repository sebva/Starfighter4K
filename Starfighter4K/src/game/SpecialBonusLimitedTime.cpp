#include "include/game/SpecialBonusLimitedTime.h"

SpecialBonusLimitedTime::SpecialBonusLimitedTime(TypeSpecialBonus bonus, int _duration, int _timeToWait, GameEngine *ge)
    :SpecialBonus(bonus, _timeToWait, ge),duration(_duration),isEnabled(false)
{

}

void SpecialBonusLimitedTime::untrigger()
{
    isEnabled = false;
}
