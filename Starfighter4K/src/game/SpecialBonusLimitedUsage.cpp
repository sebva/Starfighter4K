#include "include/game/SpecialBonusLimitedUsage.h"

SpecialBonusLimitedUsage::SpecialBonusLimitedUsage(TypeSpecialBonus bonus, int _nbActivation, int _timeToWait, GameEngine *ge)
    :SpecialBonus(bonus, _timeToWait, ge),nbActivation(_nbActivation),initialActivation(_nbActivation)
{

}

void SpecialBonusLimitedUsage::refill()
{
    nbActivation = initialActivation;
}
