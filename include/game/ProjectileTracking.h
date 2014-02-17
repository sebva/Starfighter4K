#ifndef PROJECTILETRACKING_H
#define PROJECTILETRACKING_H

#include "Projectile.h"

class GameEngine;
class Spaceship;

class ProjectileTracking : public Projectile
{
public:
    ProjectileTracking(qreal _dXOrigin, qreal _dYOrigin,Shooter _from, Spaceship* _playerFront, GameEngine* _ge);
    ~ProjectileTracking();

private:
    void advance(int _step);

    qreal dOriginAngle;
    Spaceship* spaceship;
	GameEngine* ge;
};

#endif // PROJECTILETRACKING_H
