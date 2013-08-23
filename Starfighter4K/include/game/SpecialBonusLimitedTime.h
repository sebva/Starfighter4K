#ifndef SPECIALBONUSLIMITEDTIME_H
#define SPECIALBONUSLIMITEDTIME_H

#include "SpecialBonus.h"

class SpecialBonusLimitedTime : public SpecialBonus
{
    Q_OBJECT
public:
    SpecialBonusLimitedTime(TypeSpecialBonus bonus, int _duration, int _timeToWait, GameEngine* ge);
    virtual ~SpecialBonusLimitedTime(){}

    virtual void trigger() = 0;

protected slots:
    void untrigger();

protected:
    int duration;
    bool isEnabled;
};

#endif // SPECIALBONUSLIMITEDTIME_H
