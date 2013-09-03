#include "include/game/SpecialBonusAntiGravity.h"
#include "include/engine/SoundEngine.h"

SpecialBonusAntiGravity::SpecialBonusAntiGravity(int _timeToWait, int _nbActivation, Shooter _player, GameEngine* ge)
    :SpecialBonusLimitedUsage(TypeSpecialBonusAntiGravity , _nbActivation, _timeToWait, ge), player(_player)
{

}

void SpecialBonusAntiGravity::trigger()
{
    if(nbActivation > 0)
    {
		ge->soundEngine()->playSound(AntiGravitySound);
        --nbActivation;
        ge->enableAntiGravity(player);
        if(nbActivation == 0)
            QTimer::singleShot(timeToWait,this,SLOT(refill()));
    }
}
