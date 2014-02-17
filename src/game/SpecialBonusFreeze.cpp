#include "include/game/SpecialBonusFreeze.h"
#include "include/engine/SoundEngine.h"

SpecialBonusFreeze::SpecialBonusFreeze(int _timeToWait, int _duration, Shooter _destination, GameEngine *ge)
    :SpecialBonusLimitedTime(TypeSpecialBonusFreeze, _duration,_timeToWait, ge),destination(_destination)
{

}

void SpecialBonusFreeze::trigger()
{
    if(!isEnabled)
    {
		ge->soundEngine()->playSound(FreezeSound);
        isEnabled = true;
        ge->freezePlayer(duration, destination);
        QTimer::singleShot(timeToWait, this, SLOT(untrigger()));
    }
}
