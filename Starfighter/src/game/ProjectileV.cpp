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

ProjectileV::ProjectileV(qreal _dXOrigin, qreal _dYOrigin,Shooter _from, qreal _dAmpli, qreal _dOmega)
    :Projectile(_dXOrigin,_dYOrigin,_from),
      dAmplitude(_dAmpli),//Amplitude
      dOmega(_dOmega)//Omega
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

    moveBy(dSpeed*cos(dAngle),-dAmplitude*cos(dOmega*(pos().x()-dXOrigin)));
}
