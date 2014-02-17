#ifndef PROJECTILEMULTI_H
#define PROJECTILEMULTI_H

#include "Projectile.h"

class ProjectileMulti : public Projectile
{
public:
    ProjectileMulti(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, qreal _coeff, qreal _power, qreal _dAngle);
    ~ProjectileMulti() {}

private:
    void advance(int _step);

    qreal power;
    qreal coeff;
};

#endif // PROJECTILEMULTI_H
