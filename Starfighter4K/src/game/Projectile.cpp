/*==============================================================*
 | Implementation file Projectile.cpp
 |        implements : Projectile class
 |
 |
 | summary : Entity class that represents the general behavior of a projectile.
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

#include "include/game/Projectile.h"

#include "include/config/Define.h"

Projectile::Projectile(qreal _dXOrigin, qreal _dYOrigin,Shooter _from)
    :Displayable(_dXOrigin,_dYOrigin),
      dXOrigin(_dXOrigin),//X-Origin where the projectile was shot
      dYOrigin(_dYOrigin),//Y-Origin where the projectile was shot
      from(_from),//Who has shot it
      antiGravity(false)
{
    nbPoint = NB_POINT_PROJECTILE;
    if(from == Player1)
    {
        color = new QColor(0,0,255);
        dAngle = 0;
    }
    else if(from == Player2)
    {
        color = new QColor(255,0,0);
        dAngle = M_PI;
    }
    else
        color = new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

Projectile::~Projectile()
{
    delete color;
}

void Projectile::enableAntiGravity(Shooter playerActivated)
{
    if(from != playerActivated)
    {
        antiGravity = true;
        dAngle += M_PI;
        if (cos(dAngle) >= 0)
            dAngle = 0;
        else
            dAngle = M_PI;
    }
}

QRectF Projectile::boundingRect() const
{
    return QRectF(-RADIUS_PROJECTILE/2,-RADIUS_PROJECTILE/2,RADIUS_PROJECTILE,RADIUS_PROJECTILE);
}

QPainterPath Projectile::shape() const
{
    QPainterPath l_path;
    l_path.addEllipse(-RADIUS_PROJECTILE/2,-RADIUS_PROJECTILE/2,RADIUS_PROJECTILE,RADIUS_PROJECTILE);
    return l_path;
}

void Projectile::paint(QPainter *_painter, const QStyleOptionGraphicsItem * _option, QWidget * _widget)
{
    _painter->setBrush(*color);
    _painter->drawEllipse(-RADIUS_PROJECTILE/2,-RADIUS_PROJECTILE/2,RADIUS_PROJECTILE,RADIUS_PROJECTILE);
}

void Projectile::advance(int _step)
{
    if (!_step)
        return;

    moveBy(dSpeed*cos(dAngle),-dSpeed*sin(dAngle));
}
