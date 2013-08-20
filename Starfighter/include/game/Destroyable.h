/*=====================================================================*
 | Declaration file Destroyable.h
 |      declares :  Destroyable class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef DESTROYABLE_H
#define DESTROYABLE_H

#include "include/enum/Enum.h"

class Destroyable : public QObject
{
    Q_OBJECT
public:
    Destroyable(qreal _dHealthPoint,qreal _dResistance);
    virtual ~Destroyable() {}

    virtual void receiveAttack(qreal _dPower,int _point,Shooter _forShip);
    bool gonnaDead(qreal _dPower);

signals:
    void destroyed(Destroyable* _destroyItem,int _nbPoint,Shooter _forShip);

protected:
    void isDead();

    qreal dHealthPoint;
    qreal dResistance;
    int pointToGive;
    Shooter forShip;
};
#endif
