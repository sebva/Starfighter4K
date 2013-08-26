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
#include <QMutex>

class Bonus;
class GameEngine;
class QTimer;
class SpecialBonus;
class ProjectileGuided;
class HUDWidget;

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
    qreal getPercentageSpeed() const;
    int getScore() const{return score;}
    bool getIsFrozen() const {return isFrozen;}

    void addPoint(int _point) {score+=_point;}

    qreal getXPositionFire() const {return (player == Player1) ? pos().x()+getPixmap()->width()/2.0*(1.0+cos(dAngleAttack*M_PI/180.0)) : pos().x()+getPixmap()->width()/2*(1-cos(dAngleAttack*M_PI/180.0));}
    qreal getYPositionFire() const {return (player == Player2) ? pos().y()+getPixmap()->height()/2*(1-sin(dAngleAttack*M_PI/180.0)) : pos().y()+getPixmap()->height()/2.0*(1.0+sin(dAngleAttack*M_PI/180.0));}

    qreal getXPositionCenter() const {return pos().x()+getPixmap()->width()/2.0;}
    qreal getYPositionCenter() const {return pos().y()+getPixmap()->height()/2.0;}
    void setPixmap(QPixmap* _pxmPixmap);
    void addBonus(Bonus* _bonus);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void rotate(qreal pitch);

    void freeze() {if(!isFrozen)isFrozen = true;}
    void triggerSpecialAttack();
    void triggerBonus();
    void shotTrackingBonus();
    void shotMultiBonus();
    void shotGuidedBonus();
    void disableGuideBonus();

public slots:
    void unfreeze();

private slots:
    void removeBonusInvicibility();
    void removeProjectileBonus();

private:
    void advance(int _step);

    GameEngine *gameEngine;
    HUDWidget* hud;
    QPixmap shield;    Shooter player;
	QString playerName;

    Bonus* bonus;
    SpecialBonus* specialBonus;
    QTimer *timerProjectile;
    ProjectileGuided* projectileGuided;

    TypeProjectiles type;
    TypeProjectiles oldType;

    qreal dHealthForceField;
    qreal dResistanceForceField;
    qreal dSpeed;
    qreal dAngleAttack;
    int score;
    bool isInvicible;
    bool isFrozen;
    bool isGuided;
};
#endif
