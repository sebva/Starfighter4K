#ifndef SPECIALBONUS_H
#define SPECIALBONUS_H

#include "include/engine/GameEngine.h"
#include <QObject>

class SpecialBonus : public QObject
{
    Q_OBJECT
public:
    SpecialBonus(TypeBonus _bonus, int _timeToWait, GameEngine* _ge):timeToWait(_timeToWait),ge(_ge),bonus(_bonus){}
    virtual void trigger() = 0;

    TypeBonus getTypeBonus() const {return bonus;}

protected:
    GameEngine* ge;
    int timeToWait;

private:
    TypeBonus bonus;
};

#endif // SPECIALBONUS_H
