#ifndef SPECIALBONUS_H
#define SPECIALBONUS_H

#include "include/engine/GameEngine.h"
#include <QObject>

class SpecialBonus : public QObject
{
    Q_OBJECT
public:
    SpecialBonus(int _timeToWait, GameEngine* _ge):timeToWait(_timeToWait),ge(_ge){}
    virtual void trigger() = 0;

protected:
    GameEngine* ge;
    int timeToWait;
};

#endif // SPECIALBONUS_H
