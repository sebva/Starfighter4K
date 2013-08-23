#include "include/game/SpecialBonusMulti.h"
#include "include/game/Spaceship.h"

SpecialBonusMulti::SpecialBonusMulti(int _timeToWait, int _nbActivation, Spaceship* _spaceship, GameEngine* ge)
    :SpecialBonusLimitedUsage(TypeSpecialBonusOmnidirectionalShot , _nbActivation, _timeToWait, ge), spaceship(_spaceship)
{

}

void SpecialBonusMulti::trigger()
{
    if(nbActivation > 0)
    {
        --nbActivation;
        spaceship->shotMultiBonus();
        if(nbActivation == 0)
            QTimer::singleShot(timeToWait,this,SLOT(refill()));
    }
}

