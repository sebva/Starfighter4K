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
      antiGravity(false),
      image(0)
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

void Projectile::loadPixmap()
{
    if(image != 0)
        delete image;

    if(from == Player1)
        image = new QPixmap(PICTURE_PROJ_SPACESHIP_1);
    else if(from == Player2)
        image = new QPixmap(PICTURE_PROJ_SPACESHIP_2);
    else
        image = new QPixmap(PICTURE_PROJ_SPACESHIP_3);

    setRotation(-dAngle*180.0/M_PI);
}

Projectile::~Projectile()
{
    delete color;
    if(image != 0)
        delete image;
}

void Projectile::enableAntiGravity(Shooter playerActivated)
{
    if(from != playerActivated)
    {
        if(playerActivated == Player1 && cos(dAngle) < 0 || playerActivated == Player2 && cos(dAngle) >= 0)
        {
            setRotation(180.0);
            dAngle += M_PI;
        }
        dSpeed *= SPEED_FACTOR_ANTI_GRAVITY;
        antiGravity = true;

        if (cos(dAngle) >= 0)
            dAngle = 0;
        else
            dAngle = M_PI;
    }
}

QRectF Projectile::boundingRect() const
{
    return QRectF(image->width()-15,image->height()/2.0-5,10,10);
}

QPainterPath Projectile::shape() const
{
    QPainterPath l_path;
    l_path.addEllipse(image->width()-15,image->height()/2.0-5,10,10);
    return l_path;
}

void Projectile::paint(QPainter *_painter, const QStyleOptionGraphicsItem * _option, QWidget * _widget)
{
    _painter->setBrush(*color);
    if(image != 0)
        _painter->drawPixmap(0, 0,*image);
}

void Projectile::advance(int _step)
{
    if (!_step)
        return;

    moveBy(dSpeed*cos(dAngle),-dSpeed*sin(dAngle));
}
