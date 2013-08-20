/*==============================================================*
 | Implementation file Destroyable.cpp
 |        implements : Destroyable class
 |
 |
 | summary : Represents destroyable project. All classes that
 |           extends from Destroyable have damage processing.
 |
 | Creator : Diego Antognini
 | Creation date : 27/11/2012
 | Copyright: EIAJ, all rights reserved
 |
 |
 | Version of the file : 1.0.0
 |
 *==============================================================*/

#include "include/game/Destroyable.h"

Destroyable::Destroyable(qreal _dHealthPoint,qreal _dResistance)
    :QObject(),
      dHealthPoint(_dHealthPoint),//Health Point
      dResistance(_dResistance)//Resistance
{
}

void Destroyable::receiveAttack(qreal _dPower, int _point, Shooter _forShip)
{
    this->pointToGive = _point;
    this->forShip = _forShip;
    dHealthPoint -= _dPower/dResistance;
    isDead();
}

bool Destroyable::gonnaDead(qreal _dPower)
{
    qreal l_dHealthPoint = dHealthPoint;
    l_dHealthPoint -= _dPower/dResistance;

    if(l_dHealthPoint<=0)
        return true;
    else
        return false;
}

void Destroyable::isDead()
{
    if(dHealthPoint<=0)
        emit destroyed(this,pointToGive,forShip);
}
