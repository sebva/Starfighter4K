#ifndef SPECIALBONUSANTIGRAVITY_H
#define SPECIALBONUSANTIGRAVITY_H

#include "SpecialBonusLimitedUsage.h"

class SpecialBonusAntiGravity : public SpecialBonusLimitedUsage
{
    Q_OBJECT
public:
    SpecialBonusAntiGravity(int _timeToWait, int _nbActivation, Shooter _player, GameEngine* ge);
    void trigger();

private:
    Shooter player;
};

#endif // SPECIALBONUSANTIGRAVITY_H
