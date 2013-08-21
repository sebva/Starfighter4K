/*=====================================================================*
 | Declaration file Spaceship.h
 |      declares :  Spaceship class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "include/game/Destroyable.h"
#include "include/game/Displayable.h"

#include "include/enum/Enum.h"

class Bonus;
class BonusSpeed;
class BonusProjectile;
class GameEngine;
class QTimer;

class Spaceship : public Destroyable, public Displayable
{
    Q_OBJECT
public:
    Spaceship(qreal _dX,qreal _dY,Shooter _player,const QString& _playerName,qreal _dSpeed,qreal _dHealthPoint,qreal _dResistance,GameEngine *_gameEngine);
    ~Spaceship();

    void receiveAttack(qreal _dPower);
    void attack();
    void top();
    void bottom();

    TypeItem getTypeObject() const {return tSpaceship;}
    Shooter getPlayer() const {return player;}
    QString getPlayerName() const {return playerName;}
    qreal getHealthPoint() const {return dHealthPoint;}
    qreal getHealthForceField() const {return dHealthForceField;}
    BonusProjectile* getBonusProjectile() const {return bonusProjectile;}
    qreal getPercentageSpeed() const;
    int getScore() const{return score;}

    void addPoint(int _point) {score+=_point;}

    void setPixmap(QPixmap* _pxmPixmap);
    void addBonus(Bonus* _bonus);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private slots:
    void removeSpeedBonus();
    void removeProjectileBonus();

private:
    void advance(int _step);

    GameEngine *gameEngine;

    Shooter player;
	QString playerName;

    BonusSpeed *bonusSpeed;
    BonusProjectile *bonusProjectile;
    QTimer *timerProjectile;

    TypeProjectiles type;

    qreal dHealthForceField;
    qreal dResistanceForceField;
    qreal dSpeed;
    int score;
};
#endif
