/*==============================================================*
 | Implementation file Spaceship.cpp
 |        implements : Spaceship class
 |
 |
 | summary : Entity class that represents a spaceship.
 |           A spaceship can move,fire,collect bonus,receive damage.
 |           For more information about the damage, please consult the specification file.
 |
 | Creator : Diego Antognini
 | Creation date : 27/11/2012
 | Copyright: EIAJ, all rights reserved
 |
 |
 | Version of the file : 1.0.0
 |
 *==============================================================*/

#include "include/engine/DisplayEngine.h"
#include "include/engine/GameEngine.h"
#include "include/engine/SoundEngine.h"

#include "include/game/Spaceship.h"
#include "include/game/ProjectileCross.h"
#include "include/game/ProjectileSimple.h"
#include "include/game/ProjectileV.h"
#include "include/game/BonusForceField.h"
#include "include/game/BonusHP.h"
#include "include/game/BonusProjectile.h"
#include "include/game/BonusSpeed.h"

#include "include/config/Define.h"

Spaceship::Spaceship(qreal _dX,qreal _dY,Shooter _player,const QString& _playerName,qreal _dSpeed,qreal _dHealthPoint,qreal _dResistance,GameEngine *_gameEngine)
    :Destroyable(_dHealthPoint,_dResistance),
      Displayable(_dX,_dY),
      gameEngine(_gameEngine),//GameEngine
      player(_player),//Kind of player (Player1 or Player2)
      playerName(_playerName),//Name
      bonusSpeed(0),//NULL pointer until the player receive a speed bonus
      bonusProjectile(0),//NULL pointer until the player receive a speed bonus
      timerProjectile(new QTimer(this)),//Initialize the timer for the projectile bonus, waiting to get one
      type(PROJ_SPACESHIP_DEF),//Default kind of projectile
      dHealthForceField(MAX_SPACESHIP_PV),//Health point of the force field
      dResistanceForceField(RESISTANCE_FORCE_FIELD),//Resistance of the forcefield
      dSpeed(_dSpeed),//Speed
      score(0)//Number of point, only use in timerMode
{
    if(_player == Player1)
        dAngle = 0;
    else if(_player == Player2)
        dAngle = M_PI;
    timerProjectile->setSingleShot(true);

    connect(timerProjectile,SIGNAL(timeout()),this,SLOT(removeProjectileBonus()));
}

void Spaceship::setPixmap(QPixmap *_pxmPixmap)
{
    Displayable::setPixmap(_pxmPixmap);
    if(player == Player2)
    {
        //Rotate the picture for the player2
        Displayable::setPixmap(new QPixmap(getPixmap()->transformed(QTransform().rotate(180))));
        setPos(pos().x()-getPixmap()->size().width(),pos().y());
    }
}

Spaceship::~Spaceship()
{
    delete bonusSpeed;
    delete bonusProjectile;
    delete timerProjectile;
}

QRectF Spaceship::boundingRect() const
{
    return QRectF(getPixmap()->rect());
}

QPainterPath Spaceship::shape() const
{
    QPainterPath l_path;
    l_path.addEllipse(boundingRect());
    return l_path;
}

void Spaceship::paint(QPainter *_painter,const QStyleOptionGraphicsItem *_option, QWidget *_widget)
{
    _painter->drawPixmap(0,0,*getPixmap());
}

qreal Spaceship::getPercentageSpeed() const
{
    if(bonusSpeed==0)
        return 100.0;
    else
        return 100.0+bonusSpeed->getSpeed()/(dSpeed-bonusSpeed->getSpeed())*100.0;
}

void Spaceship::addBonus(Bonus *_bonus)
{
    if(BonusHP* bhp = dynamic_cast<BonusHP*>(_bonus))
    {
        dHealthPoint+=bhp->getHealthPoint();
        if(dHealthPoint>MAX_SPACESHIP_PV)
            dHealthPoint=MAX_SPACESHIP_PV;
        delete bhp;
    }
    else if(BonusProjectile* bp = dynamic_cast<BonusProjectile*>(_bonus))
    {
        //If a timer for projectile is already started, we need to stop it and start anothero ne
        if(timerProjectile->isActive())
            removeProjectileBonus();

        type = bp->getType();
        bonusProjectile = bp;

        timerProjectile->start(bp->getExpiration());
    }
    else if(BonusForceField* bff = dynamic_cast<BonusForceField*>(_bonus))
    {
        dHealthForceField = MAX_SPACESHIP_PV;
        delete bff;
    }
    else if(BonusSpeed* bs = dynamic_cast<BonusSpeed*>(_bonus))
    {
        if(bonusSpeed==0)
        {
            bonusSpeed = bs;
            dSpeed+=bs->getSpeed();
            QTimer::singleShot(bs->getExpiration(),this,SLOT(removeSpeedBonus()));
        }
        else
            delete bs;
    }
}

void Spaceship::removeProjectileBonus()
{
    delete bonusProjectile;
    bonusProjectile = 0;
    timerProjectile->stop();
    type = PROJ_SPACESHIP_DEF;
}

void Spaceship::removeSpeedBonus()
{
    dSpeed-=bonusSpeed->getSpeed();
    delete bonusSpeed;
    bonusSpeed = 0;
}

void Spaceship::receiveAttack(qreal _dPower)
{
    double power1 = _dPower * (100.0 - dHealthForceField) / 100.0;
    double power2 = _dPower - power1;
	
	dHealthPoint -= power1 / dResistance;
    dHealthForceField -= power2 / dResistanceForceField;
    if(dHealthForceField < 0)
        dHealthForceField = 0;

    if(dHealthPoint<=0)
        dHealthPoint=0;
    isDead();
}

void Spaceship::attack()
{
    int l_x = 0;
    int l_y = 0;

    if(player==Player1)
        l_x = pos().x()+getPixmap()->width();
    else
        l_x = pos().x();//Don't need to remove the width of the QPixmap,already done in the constructor

    l_y = pos().y()+getPixmap()->height()/2;

    gameEngine->soundEngine()->playSound(ShootSound);

    switch(type)
    {
        case ProjSimple:
            gameEngine->addProjectile(new ProjectileSimple(l_x,l_y,player));
            break;

        case ProjCross:
            for(int i = 0;i<3;i++)
                gameEngine->addProjectile(new ProjectileCross(l_x,l_y,player,i-1));
            break;

        case ProjV:
            gameEngine->addProjectile(new ProjectileV(l_x,l_y,player,AMPLI_SPACESHIP_PROJ_V,OMEGA_SPACESHIP_PROJ_V));
            break;
        case ProjAlien:
            break;

        case Nothing:
            break;
    }
}

void Spaceship::top()
{
    if((pos().y()-dSpeed)<=gameEngine->displayEngine()->sceneSize().y())
        setPos(pos().x(),gameEngine->displayEngine()->sceneSize().y());
    else
        setPos(pos().x(),pos().y()-dSpeed);
}

void Spaceship::bottom()
{
    if((pos().y()+getPixmap()->height()+dSpeed)>=gameEngine->displayEngine()->sceneSize().height())
        setPos(pos().x(),gameEngine->displayEngine()->sceneSize().height()-getPixmap()->height());
    else
        setPos(pos().x(),pos().y()+dSpeed);
}

void Spaceship::advance(int _step)
{
    if (!_step)
        return;
}
