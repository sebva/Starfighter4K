#include "include/game/ProjectileMulti.h"
#include "include/config/Define.h"

ProjectileMulti::ProjectileMulti(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, qreal _coeff, qreal _power, qreal _dAngle)
    :Projectile(_dXOrigin, _dYOrigin, _from),coeff(_coeff),power(_power)
{
    dAngle = -_dAngle;
    dPower = POWER_MULTI;
    dSpeed = SPEED_MULTI_DEF;

    if(from == Player2)
        dAngle += M_PI;

    loadPixmap();
}


void ProjectileMulti::advance(int _step)
{
    if (!_step)
        return;

    if(antiGravity)
        Projectile::advance(_step);
    else
    {
        resetTransform();
        qreal x = dSpeed*cos(dAngle);
        qreal y = -dSpeed*coeff*pow(abs(pos().x()-dXOrigin), power);
        setPos(pos().x()+x, dYOrigin+y);

        if(from == Player1)
            setRotation(-2*dAngle*180.0/M_PI);
        else
            setRotation(180.0);

        x = pos().x();
        y = 0;

        if(from == Player1)
            setTransform(QTransform().translate(x,y).rotateRadians(dAngle).translate(-x,-y));
        else
        {
            x = dXOrigin-pos().x();
            setTransform(QTransform().translate(x,y).rotateRadians(M_PI-dAngle).translate(-x,-y));
        }
    }
}
