#ifndef SPECIALBONUSFREEZE_H
#define SPECIALBONUSFREEZE_H

#include "SpecialBonusLimitedTime.h"
#include "include/enum/Enum.h"

class SpecialBonusFreeze : public SpecialBonusLimitedTime
{
    Q_OBJECT
public:
    SpecialBonusFreeze(int _timeToWait, int _duration, Shooter _destination, GameEngine* ge);
    void trigger();

private:
    Shooter destination;
};

#endif // SPECIALBONUSFREEZE_H
