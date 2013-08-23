#include "include/game/SpecialBonusTracking.h"
#include "include/game/Spaceship.h"

SpecialBonusTracking::SpecialBonusTracking(int _timeToWait, int _nbActivation, Spaceship* _spaceship, GameEngine* ge)
    :SpecialBonusLimitedUsage(TypeSpecialBonusOmnidirectionalShot , _nbActivation, _timeToWait, ge), spaceship(_spaceship)
{

}

void SpecialBonusTracking::trigger()
{
    if(nbActivation > 0)
    {
        --nbActivation;
        spaceship->shotTrackingBonus();
        if(nbActivation == 0)
            QTimer::singleShot(timeToWait,this,SLOT(refill()));
    }
}
