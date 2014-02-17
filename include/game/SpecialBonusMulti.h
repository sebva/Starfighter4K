#ifndef SPECIALBONUSMULTI_H
#define SPECIALBONUSMULTI_H

#include "SpecialBonusLimitedUsage.h"

class SpecialBonusMulti : public SpecialBonusLimitedUsage
{
    Q_OBJECT
public:
    SpecialBonusMulti(int _timeToWait, int _nbActivation, Spaceship* _spaceship, GameEngine* ge);
    void trigger();

private:
    Spaceship* spaceship;
};

#endif // SPECIALBONUSMULTI_H
