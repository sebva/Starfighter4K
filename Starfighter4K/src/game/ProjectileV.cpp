/*==============================================================*
 | Implementation file ProjectileV.cpp
 |        implements : ProjectileV class
 |
 |
 | summary : Entity class that represents the exactly behavior of a V projectile.
 |           For more information, please consult the specification file
 |
 | Creator : Diego Antognini
 | Creation date : 27/11/2012
 | Copyright: EIAJ, all rights reserved
 |
 |
 | Version of the file : 1.0.0
 |
 *==============================================================*/

#include "include/game/ProjectileV.h"

#include "include/config/Define.h"

ProjectileV::ProjectileV(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, qreal _dAmpli, qreal _dOmega, qreal _dAngle)
    :Projectile(_dXOrigin,_dYOrigin,_from),
      dAmplitude(_dAmpli),//Amplitude
      dOmega(_dOmega),//Omega
      dAngle2(-_dAngle)
{
    dAngle = 0;
    if(_from == Player2)
        dAngle += M_PI;

    dPower = POWER_V;
    dSpeed = SPEED_V_DEF;
}

void ProjectileV::advance(int _step)
{
    if (!_step)
        return;

    resetTransform();
    qreal x = dSpeed*cos(dAngle);
    qreal y = -(dAmplitude*cos(dOmega*(pos().x()-dXOrigin)));

    if(from == Player1 && pos().x()-dXOrigin > dOmega*(1.75*M_PI*180.0/M_PI-dXOrigin)*180.0/M_PI
            || from == Player2 && abs(pos().x()-dXOrigin) > abs(dOmega*(9.25*M_PI*180.0/M_PI-dXOrigin))*180.0/M_PI)
        moveBy(x,0);
    else
        if(from == Player1 && dAngle2 < 0 || from == Player2 && dAngle2 > 0)
            moveBy(x,-y);
        else
            moveBy(x, y);

    x = pos().x();
    y = 0;

    if(from == Player1)
        setTransform(QTransform().translate(x,y).rotateRadians(dAngle2).translate(-x,-y));
    else
    {
        x -= dXOrigin;
        setTransform(QTransform().translate(-x,-y).rotateRadians(-dAngle2).translate(x,y));
    }
}
