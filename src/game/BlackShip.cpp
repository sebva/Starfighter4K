#include "include/game/BlackShip.h"
#include "include/engine/GameEngine.h"
#include "include/config/Define.h"
#include "include/game/ProjectileBlack.h"

Blackship::Blackship(qreal _dXOrigin, qreal _dYOrigin, qreal _dHealthPoint,qreal _dResistance,GameEngine* _gameEngine,SizeFire _sizeFire)
    :Displayable(_dXOrigin, _dYOrigin, new QPixmap(PICTURE_BLACKSHIP)),Destroyable(_dHealthPoint, _dResistance),gameEngine(_gameEngine),sizeFire(_sizeFire),dSpeed(SPEED_BLACKSHIP),distance(0)
{
    nbPoint = NB_POINT_BLACKSHIP;
}

QRectF Blackship::boundingRect() const
{
    return QRectF(getPixmap()->rect());
}

QPainterPath Blackship::shape() const
{
    QPainterPath l_path;
    l_path.addEllipse(boundingRect());
    return l_path;
}

void Blackship::paint(QPainter *_painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    _painter->drawPixmap(0,0,*getPixmap());
}

void Blackship::advance(int _step)
{
    if (!_step)
        return;

    ++distance;
    if(distance >= INTERVAL_ATTACK_DISTANCE_BLACKSHIP)
    {
        distance = 0;
        attack();
    }
    moveBy(0,dSpeed);
}

void Blackship::attack()
{
    int width = getPixmap()->width();
    int height = getPixmap()->height();
    switch(sizeFire)
    {
        case sBoth:
            gameEngine->addProjectile(new ProjectileBlack(pos().x()+width/3.0,pos().y()+1.5*height/2.0,Black,M_PI-ANGLE_FIRST_BLACKSHIP_FIRE));
            gameEngine->addProjectile(new ProjectileBlack(pos().x()+2*width/3.0,pos().y()+height/2.0,Black,ANGLE_FIRST_BLACKSHIP_FIRE));
        break;

        case sLeft1:
            gameEngine->addProjectile(new ProjectileBlack(pos().x()+width/3.0,pos().y()+1.5*height/2.0,Black,M_PI-ANGLE_SECOND_BLACKSHIP_FIRE));
            break;

        case sRight1:
            gameEngine->addProjectile(new ProjectileBlack(pos().x()+2*width/3.0,pos().y()+height/2.0,Black,ANGLE_SECOND_BLACKSHIP_FIRE));
            break;

        case sLeft2:
            gameEngine->addProjectile(new ProjectileBlack(pos().x()+width/3.0,pos().y()+1.5*height/2.0,Black,M_PI-ANGLE_THIRD_BLACKSHIP_FIRE));
            break;

        case sRight2:
            gameEngine->addProjectile(new ProjectileBlack(pos().x()+2*width/3.0,pos().y()+height/2.0,Black,ANGLE_THIRD_BLACKSHIP_FIRE));
            break;

        default:
            break;
    }
}

void Blackship::createBlackSquadron(GameEngine* gameEngine)
{
    Blackship* bs1 = new Blackship(0,0,MAX_SPACESHIP_PV,RESISTANCE_BLACKSHIP,gameEngine,sBoth);
    int width = bs1->getPixmap()->width();
    int height = bs1->getPixmap()->height();
    bs1->setPos(gameEngine->sceneSize().width()/2.0-width/2.0,-height);

    int padding = 5;

    Blackship* bs2 = new Blackship(gameEngine->sceneSize().width()/2.0-2*(width/2.0+padding),-2*(height+padding),MAX_SPACESHIP_PV,RESISTANCE_BLACKSHIP,gameEngine,sLeft1);
    Blackship* bs3 = new Blackship(gameEngine->sceneSize().width()/2.0-3*(width/2.0+padding),-3*(height+padding),MAX_SPACESHIP_PV,RESISTANCE_BLACKSHIP,gameEngine,sLeft2);
    Blackship* bs4 = new Blackship(gameEngine->sceneSize().width()/2.0+width/5.0+padding,-2*(height+padding),MAX_SPACESHIP_PV,RESISTANCE_BLACKSHIP,gameEngine,sRight1);
    Blackship* bs5 = new Blackship(gameEngine->sceneSize().width()/2.0+2*(width/5.0+padding),-3*(height+padding),MAX_SPACESHIP_PV,RESISTANCE_BLACKSHIP,gameEngine,sRight2);

    QList<Blackship*> blackships;
    blackships << bs1 << bs2 << bs3 << bs4 << bs5;

    for(auto it = blackships.begin(); it != blackships.end(); ++it)
        gameEngine->addBlackship(*it);
}
