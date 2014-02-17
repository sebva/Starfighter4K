/*=====================================================================*
 | Declaration file Displayable.h
 |      declares :  Displayable class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "include/enum/Enum.h"

class QPixmap;

class Displayable : public QGraphicsItem
{
public:
    Displayable(qreal _dX, qreal _dY, QPixmap* _pixmap = 0);
    virtual ~Displayable();

    QSize sizePixmap() const {return isPixmap()?pxmPicture->size():QSize();}  
    int getNbPoint() const {return nbPoint;}
    QPixmap* getPixmap() const {return pxmPicture;}
    bool isPixmap() const {return !pxmPicture==0;}

    virtual TypeItem getTypeObject() const=0;
    virtual qreal getPower() const {return 0.0;}
    virtual void advance(int _step)=0;

    qreal getAngle() const {return dAngle;}

    virtual QRectF boundingRect() const=0;
    virtual QPainterPath shape() const=0;
    virtual void paint(QPainter *_painter, const QStyleOptionGraphicsItem *_option, QWidget *_widget) = 0;


    void setPos(qreal _dX, qreal _dY);
    virtual void setPixmap(QPixmap* _pxmPixmap);

protected:
    int nbPoint;
    qreal dAngle;
private:
    qreal dX;
    qreal dY;
    QPixmap* pxmPicture;
};
#endif
