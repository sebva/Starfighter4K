/*==============================================================*
 | Implementation file Displayable.cpp
 |        implements : Displayable class
 |
 |
 | summary : Represents all objects that will be in the scene.
 |
 | Creator : Diego Antognini
 | Creation date : 27/11/2012
 | Copyright: EIAJ, all rights reserved
 |
 |
 | Version of the file : 1.0.0
 |
 *==============================================================*/

#include "include/game/Displayable.h"

Displayable::Displayable(qreal _dX, qreal _dY, QPixmap* _pixmap)
    :nbPoint(0),//Number of point
      dX(_dX),//X coordinate
      dY(_dY),//Y coordinate
      pxmPicture(_pixmap)//Picture

{
    dAngle = 0;
    setPos(dX,dY);
}

Displayable::~Displayable()
{
    delete pxmPicture;
}

void Displayable::setPos(qreal _dX, qreal _dY)
{
    dX=_dX;
    dY=_dY;
    QGraphicsItem::setPos(dX,dY);
}

void Displayable::setPixmap(QPixmap *_pxmPixmap)
{
    if(pxmPicture!=0)
        delete pxmPicture;
    pxmPicture = _pxmPixmap;
}
