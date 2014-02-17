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

    void loadPixmap();

    TypeItem getTypeObject() const {return tProj;}
    Shooter getFrom() const {return from;}

    virtual void enableAntiGravity(Shooter playerActivated);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *_painter, const QStyleOptionGraphicsItem *, QWidget *);

    virtual void advance(int _step);

protected:
    qreal dPower;
    qreal dXOrigin;
    qreal dYOrigin;

    bool antiGravity;

    qreal dSpeed;
    QColor* color;
    QPixmap* image;

    Shooter from;
};
#endif
