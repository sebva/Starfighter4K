#include "include/game/SpecialBonusTracking.h"
#include "include/engine/SoundEngine.h"
#include "include/game/Spaceship.h"

SpecialBonusTracking::SpecialBonusTracking(int _timeToWait, int _nbActivation, Spaceship* _spaceship, GameEngine* ge)
    :SpecialBonusLimitedUsage(TypeSpecialBonusTrackingMissile , _nbActivation, _timeToWait, ge), spaceship(_spaceship)
{

}

void SpecialBonusTracking::trigger()
{
    if(nbActivation > 0)
    {
		ge->soundEngine()->playSound(TrackingSound);
        --nbActivation;
        spaceship->shotTrackingBonus();
        if(nbActivation == 0)
            QTimer::singleShot(timeToWait,this,SLOT(refill()));
    }
}
