#ifndef PROJECTILEGUIDED_H
#define PROJECTILEGUIDED_H

#include "Projectile.h"

class Spaceship;

class ProjectileGuided : public Projectile
{
public:
    ProjectileGuided(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, Spaceship* _spaceship);
    ~ProjectileGuided();

    void top();
    void bottom();

private:
    Spaceship* spaceship;
};

#endif // PROJECTILEGUIDED_H
