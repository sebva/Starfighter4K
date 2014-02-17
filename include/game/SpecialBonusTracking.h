#ifndef SPECIALBONUSTRACKING_H
#define SPECIALBONUSTRACKING_H

#include "include/game/SpecialBonusLimitedUsage.h"

class Spaceship;

class SpecialBonusTracking : public SpecialBonusLimitedUsage
{
    Q_OBJECT
public:
    SpecialBonusTracking(int _timeToWait, int _nbActivation, Spaceship* _spaceship, GameEngine* ge);
    void trigger();

private:
    Spaceship* spaceship;
};

#endif // SPECIALBONUSTRACKING_H
