#ifndef SPECIALBONUS_H
#define SPECIALBONUS_H

#include "include/engine/GameEngine.h"
#include <QObject>

class SpecialBonus : public QObject
{
    Q_OBJECT
public:
    SpecialBonus(TypeSpecialBonus _bonus, int _timeToWait, GameEngine* _ge):timeToWait(_timeToWait),ge(_ge),bonus(_bonus){}
    virtual ~SpecialBonus(){}

    virtual void trigger() = 0;

    TypeSpecialBonus getTypeBonus() const {return bonus;}

protected:
    GameEngine* ge;
    int timeToWait;

private:
    TypeSpecialBonus bonus;
};

#endif // SPECIALBONUS_H
