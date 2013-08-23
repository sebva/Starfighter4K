#include "include/game/ProjectileMulti.h"
#include "include/config/Define.h"

ProjectileMulti::ProjectileMulti(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, qreal _coeff, qreal _power)
    :Projectile(_dXOrigin, _dYOrigin, _from),coeff(_coeff),power(_power)
{
    dPower = POWER_MULTI;
    dSpeed = SPEED_MULTI_DEF;
}


void ProjectileMulti::advance(int _step)
{
    if (!_step)
        return;

    if(antiGravity)
        Projectile::advance(_step);
    else
    {
        qreal x = dSpeed*cos(dAngle);
        qreal y = -dSpeed*coeff*pow(abs(pos().x()-dXOrigin), power);

        setPos(pos().x()+x, dYOrigin+y);
    }
}
