#ifndef BLACKSHIP_H
#define BLACKSHIP_H

#include "include/game/Displayable.h"
#include "include/game/Destroyable.h"

#include "include/enum/Enum.h"
#include "include/config/Define.h"

class GameEngine;

class Blackship : public Displayable, public Destroyable
{
public:
    Blackship(qreal _dXOrigin, qreal _dYOrigin, qreal _dHealthPoint,qreal _dResistance,GameEngine* _gameEngine,SizeFire _sizeFire);
    ~Blackship(){}

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *_painter, const QStyleOptionGraphicsItem *, QWidget *);

    TypeItem getTypeObject() const {return tBlackShip;}

    static void createBlackSquadron(GameEngine *gameEngine);

private:
    void advance(int _step);
    void attack();

    qreal dSpeed;
    int distance;

    GameEngine* gameEngine;
    SizeFire sizeFire;
};

#endif // BLACKSHIP_H
