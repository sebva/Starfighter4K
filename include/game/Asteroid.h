/*=====================================================================*
 | Declaration file Asteroid.h
 |      declares :  Asteroid class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef ASTEROID_H
#define ASTEROID_H

#include "include/game/Destroyable.h"
#include "include/game/Projectile.h"

#include "include/enum/Enum.h"
#include "include/config/Define.h"

class GameEngine;

class Asteroid : public Destroyable, public Projectile
{
public:
    Asteroid(qreal _dX, qreal _dY,Shooter _from, qreal _dResistance, qreal _dHealthPoint, GameEngine *_gameEngine,int _idParent=0,qreal _dAngle=0,qreal _dSpeedParent = 0);
    ~Asteroid() {}

    bool isSmall() const {return bSmall;}
    int getIdParent() const {return idParent;}
    TypeItem getTypeObject() const {return (bSmall)?tSmallAsteroid:tAsteroid;}
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void collision(qreal _dAngle);

protected:
    int currentFrame;
    int numberFrameMin;
    int numberFrameMax;

private:
    GameEngine* gameEngine;

    int index;

    int idParent;

    bool bSmall;
};
#endif
