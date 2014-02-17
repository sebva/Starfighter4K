#include "include/game/SpecialBonusGuided.h"
#include "include/config/Define.h"
#include "include/game/Spaceship.h"

SpecialBonusGuided::SpecialBonusGuided(int _timeToWait, int _nbActivation, Spaceship* _spaceship, GameEngine* ge)
    :SpecialBonusLimitedUsage(TypeSpecialBonusGuidedMissile, _nbActivation, _timeToWait, ge), spaceship(_spaceship)
{

}

void SpecialBonusGuided::trigger()
{
    if(nbActivation > 0)
    {
        --nbActivation;
        spaceship->shotGuidedBonus();
        if(nbActivation == 0)
            QTimer::singleShot(timeToWait,this,SLOT(refill()));
    }
}
