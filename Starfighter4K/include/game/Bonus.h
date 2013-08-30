/*=====================================================================*
 | Declaration file Bonus.h
 |      declares :  Bonus class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef BONUS_H
#define BONUS_H

#include "include/game/Displayable.h"

#include "include/config/Define.h"

class GameEngine;

class Bonus : public QObject, public Displayable
{
    Q_OBJECT
public:
    Bonus(TypeBonus _bonus, GameEngine *_gameEngine);
    virtual ~Bonus();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *_painter, const QStyleOptionGraphicsItem *, QWidget *);

    TypeItem getTypeObject() const {return tBonus;}
    TypeBonus getTypeBonus() const {return bonus;}
    void advance(int _step);

private:
    static const qreal kIntervalArgument;

    GameEngine *gameEngine;
    TypeBonus bonus;

    qreal dArgument;
    qreal dModule;
    qreal dX0;
    qreal dY0;
    int k;
    int directionX;
    int directionY;
    int directionArg;

};
#endif
