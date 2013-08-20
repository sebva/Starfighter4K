/*=====================================================================*
 | Declaration file Supernova.h
 |      declares :  Supernova class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef SUPERNOVA_H
#define SUPERNOVA_H

#include "include/config/Define.h"
#include "include/enum/Enum.h"

class GameEngine;

class Supernova
{
public:
    Supernova(qreal _dX, qreal _dY,GameEngine *_gameEngine);
    ~Supernova();

    TypeItem getTypeObject() const {return tSupernova;}

private:
    static const int nbSpirales = NB_SPIRAL;

    GameEngine* gameEngine;

    qreal dX;
    qreal dY;
};
#endif
