/*=====================================================================*
 | Declaration file Projectile.h
 |      declares :  Projectile class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "include/game/Displayable.h"

#include "include/enum/Enum.h"

class QColor;

class Projectile : public Displayable
{
public:
    Projectile(qreal _dXOrigin, qreal _dYOrigin,Shooter _from);
    virtual ~Projectile();

    qreal getPower() const {return dPower;}

    TypeItem getTypeObject() const {return tProj;}
    Shooter getFrom() const {return from;}

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *_painter, const QStyleOptionGraphicsItem *_option, QWidget *_widget);

    virtual void advance(int _step);

protected:
    qreal dPower;
    qreal dXOrigin;
    qreal dYOrigin;

    qreal dSpeed;
    QColor* color;

    Shooter from;
};
#endif
