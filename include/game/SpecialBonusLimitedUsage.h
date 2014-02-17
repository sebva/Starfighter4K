#ifndef SPECIALBONUSLIMITEDUSAGE_H
#define SPECIALBONUSLIMITEDUSAGE_H

#include "SpecialBonus.h"

class SpecialBonusLimitedUsage : public SpecialBonus
{
    Q_OBJECT
public:
    SpecialBonusLimitedUsage(TypeSpecialBonus bonus, int _nbActivation, int _timeToWait, GameEngine* ge);
    virtual ~SpecialBonusLimitedUsage(){}

    virtual void trigger() = 0;
    int getNbActivation() { return nbActivation; }
    int getInitialActivation() { return initialActivation; }

public slots:
    void refill();

protected:
    int nbActivation;
    int initialActivation;
};

#endif // SPECIALBONUSLIMITEDUSAGE_H
