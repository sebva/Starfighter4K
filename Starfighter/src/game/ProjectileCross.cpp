/*==============================================================*
 | Implementation file ProjectileCross.cpp
 |        implements : ProjectileCross class
 |
 |
 | summary : Entity class that represents the exactly behavior of a cross projectile.
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

#include "include/game/ProjectileCross.h"

#include "include/config/Define.h"

ProjectileCross::ProjectileCross(qreal _dXOrigin, qreal _dYOrigin, Shooter _from,int _nb)
    :Projectile(_dXOrigin,_dYOrigin,_from)
{
    dSpeed = SPEED_CROSS_DEF;
    dPower = POWER_CROSS;

    dAngle = 0;

    if(_nb==-1)
        dAngle = -SLOPE_CROSS;
    else if(_nb==1)
        dAngle = SLOPE_CROSS;

    if(_from==Player2)
        dAngle+=M_PI;
}

