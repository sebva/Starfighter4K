/*==============================================================*
 | Implementation file Bonus.cpp
 |        implements : Bonus class
 |
 |
 | summary : Entity class that represents a bonus.
 |           For more information, please consult the specification file
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
#include "include/engine/SpawnEngine.h"

#include "include/game/Bonus.h"
#include "include/game/Spaceship.h"

const qreal Bonus::kIntervalArgument = ARG_INCREMENTATION_BONUS;

Bonus::Bonus(TypeBonus _bonus, GameEngine *_gameEngine)
    :Displayable(0,0,new QPixmap(PICTURE_BONUS)),
      gameEngine(_gameEngine),//GameEngine
      directionX(1),//Default X-direction
      directionY(1),//Default Y-direction
      directionArg(1),//Defaut Arg-direction
      bonus(_bonus)
{
    dAngle = M_PI/2.0;

    //Points for the timer Mode
    nbPoint = NB_POINT_BONUS;

    /*Generate the position of the Bonus
      For more informations cf the specification file*/
    int l_Xmin = gameEngine->xminWarzone();
    int l_Xmax = gameEngine->xmaxWarZone();

    int l_x1 = gameEngine->randInt(l_Xmax-getPixmap()->width()-l_Xmin)+l_Xmin;

    if(l_x1>=(l_Xmax-l_Xmin)/2.0)
        l_x1-=DELTA_X;
    else
        l_x1+=DELTA_X;

    int l_x2 = l_x1;

    if(gameEngine->randInt(1))
        l_x2+=DELTA_X_B;
    else
        l_x2-=DELTA_X_B;

    //To avoid to enter in the player's zone
    if(fabs(static_cast<double>(l_x2-l_x1))<DELTA_X_B/2.0)
    {
        if(l_x2>l_x1)
            l_x2-=DELTA_X_B/2.0;
        else
            l_x2+=DELTA_X_B/2.0;
    }

    int l_x3 = l_x1;

    int l_y1 = gameEngine->sceneSize().y();
    int l_y2 = gameEngine->sceneSize().height()/2.0;
    int l_y3 = gameEngine->sceneSize().height();

    /*Calculate the trajectory. There are 4 possibilities :
    1) Top->Bottom x2<xg
    2) Top->Bottom x2>=xg
    3) Bottom->Top x2<xg
    4) Bottom->Top x2>=xg
    */

    if(l_x2>l_x1)
        directionArg=-1;
    else
    {
        directionX=-1;
        directionY=-1;
    }

    if(gameEngine->randInt(2)==1)//1 = bottom,0 = top
    {
        directionArg*=-1;
        dAngle=-M_PI/2.0;
        l_y1=gameEngine->sceneSize().height();
        l_y3=gameEngine->sceneSize().y();
        //Rotate the picture if it's coming by the bottom size
        Displayable::setPixmap(new QPixmap(getPixmap()->transformed(QTransform().rotate(180))));
    }

    //Change Y location if the case where the Bonus comes by the top,
    //we should remove the height to have a better apparition
    if(l_y1==gameEngine->sceneSize().y())
        l_y1-=getPixmap()->height();

    dX0 = (l_x3*l_x3*(l_y1-l_y2)+(l_x1*l_x1+(l_y1-l_y2)*(l_y1-l_y3))*(l_y2-l_y3)+l_x2*l_x2*(l_y3-l_y1))
            /(2.0*(l_x3*(l_y1-l_y2)+l_x1*(l_y2-l_y3)+l_x2*(l_y3-l_y1)));

    dY0 = (-l_x2*l_x2*l_x3+l_x1*l_x1*(l_x3-l_x2)+l_x3*(l_y1-l_y2)*(l_y1+l_y2)+l_x1*(l_x2*l_x2-l_x3*l_x3+l_y2*l_y2-l_y3*l_y3)+l_x2*(l_x3*l_x3-l_y1*l_y1+l_y3*l_y3))
            /(2.0*(l_x3*(l_y1-l_y2)+l_x1*(l_y2-l_y3)+l_x2*(l_y3-l_y1)));

    dModule = sqrt((l_x1-dX0)*(l_x1-dX0)+(l_y1-dY0)*(l_y1-dY0));
    dArgument = atan((dY0-l_y1)/(l_x1-dX0));

    setPos(l_x1,l_y1);
}

Bonus::~Bonus()
{
}

void Bonus::advance(int _step)
{
    if (!_step)
        return;

    dArgument+=directionArg*kIntervalArgument;

    setPos(dX0+directionX*dModule*cos(dArgument)
           ,dY0-directionY*dModule*sin(dArgument));
}

QRectF Bonus::boundingRect() const
{
    return QRectF(getPixmap()->rect());
}

QPainterPath Bonus::shape() const
{
    QPainterPath l_path;
    l_path.addEllipse(boundingRect());
    return l_path;
}

void Bonus::paint(QPainter *_painter,const QStyleOptionGraphicsItem *, QWidget *)
{
    _painter->drawPixmap(0,0,*getPixmap());
}
