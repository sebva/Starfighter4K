/*==============================================================*
 | Implementation file ProjectileAlien.cpp
 |        implements : ProjectileAlien class
 |
 |
 | summary : Entity class that represents the exactly behavior of an alien projectile.
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

#include "include/game/ProjectileAlien.h"

#include "include/config/Define.h"

const qreal ProjectileAlien::kIntervalModule = MODULE_INCREMENT_ALIEN;

ProjectileAlien::ProjectileAlien(qreal _dXOrigin, qreal _dYOrigin,Shooter _from, qreal _dArgument, qreal _dModule)
    ://Displayable(_dXOrigin,_dYOrigin),
      Projectile(_dXOrigin,_dYOrigin,_from),
      dModule(_dModule)//Module
{
    dAngle = _dArgument;
    dPower = POWER_ALIEN;
}

void ProjectileAlien::advance(int _step)
{
    if (!_step)
        return;

    dModule+=ProjectileAlien::kIntervalModule;

    if(antiGravity)
        moveBy(SPEED_SIMPLE_DEF*SPEED_FACTOR_ANTI_GRAVITY*0.5*cos(dAngle), 0);
    else
        setPos(dXOrigin+dModule*cos(dAngle), dYOrigin-dModule*sin(dAngle));
}
