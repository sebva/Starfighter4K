#ifndef SPECIALBONUSGUIDED_H
#define SPECIALBONUSGUIDED_H

#include "SpecialBonusLimitedUsage.h"

class Spaceship;

class SpecialBonusGuided : public SpecialBonusLimitedUsage
{
    Q_OBJECT
public:
    SpecialBonusGuided(int _timeToWait, int _nbActivation, Spaceship* _spaceship, GameEngine* ge);
    void trigger();

private:
    Spaceship* spaceship;
};

#endif // SPECIALBONUSGUIDED_H
