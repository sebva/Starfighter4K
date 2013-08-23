#ifndef PROJECTILETRACKING_H
#define PROJECTILETRACKING_H

#include "Projectile.h"

class Spaceship;

class ProjectileTracking : public Projectile
{
public:
    ProjectileTracking(qreal _dXOrigin, qreal _dYOrigin,Shooter _from, Spaceship* _playerFront);
    ~ProjectileTracking() {}

private:
    void advance(int _step);

    qreal dOriginAngle;
    Spaceship* spaceship;
};

#endif // PROJECTILETRACKING_H
