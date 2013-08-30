#include "include/game/ProjectileBlack.h"

#include "include/config/Define.h"

ProjectileBlack::ProjectileBlack(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, qreal _dAngle)
    :Projectile(_dXOrigin,_dYOrigin,_from)
{
    dAngle = -_dAngle;

    dPower = POWER_BLACKSHIP_PROJECTILE;
    dSpeed = SPEED_BLACKSHIP_PROJECTILE;

    loadPixmap();
}
