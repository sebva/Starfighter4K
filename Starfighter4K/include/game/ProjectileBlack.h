#ifndef PROJECTILEBLACK_H
#define PROJECTILEBLACK_H

#include "ProjectileSimple.h"

class ProjectileBlack : public Projectile
{
public:
    ProjectileBlack(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, qreal _dAngle);
    ~ProjectileBlack() {}
};

#endif // PROJECTILEBLACK_H
