/*=====================================================================*
 | Declaration file Alienspaceship.h
 |      declares :  Alienspaceship class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef ALIEN_SPACESHIP_H
#define ALIEN_SPACESHIP_H

#include "include/game/Displayable.h"
#include "include/game/Destroyable.h"

#include "include/enum/Enum.h"
#include "include/config/Define.h"

class GameEngine;

class AlienSpaceship : public Displayable, public Destroyable
{
public:
    AlienSpaceship(int _nbSpirales,qreal _dHealthPoint,qreal _dResistance,GameEngine* _gameEngine);
    ~AlienSpaceship(){}

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *_painter, const QStyleOptionGraphicsItem *_option, QWidget *_widget);

    TypeItem getTypeObject() const {return tAlien;}
private:
    void advance(int _step);
    void attacking();

    static const qreal kIntervalArgument;

    GameEngine* gameEngine;
    QImage shadow;

	int nbSpirales;

    bool isAttacking;
    bool hasAttacked;

    qreal dArgument;
    qreal dModule;
    qreal dX0;
    qreal dY0;
    int yStop;
    qreal blink;
    bool raisingEdge;

    int directionX;
    int directionY;
    int directionArg;
};
#endif
