#ifndef ASTEROIDSUPERNOVA_H
#define ASTEROIDSUPERNOVA_H

#include "include/config/Define.h"
#include "include/game/Asteroid.h"

class AsteroidSupernova : public Asteroid
{
public:
    AsteroidSupernova(qreal _dX, qreal _dY,Shooter _from, qreal _dResistance, qreal _dHealthPoint, GameEngine *_gameEngine,qreal _dAngle);
    ~AsteroidSupernova() {}
};

#endif // ASTEROIDSUPERNOVA_H
