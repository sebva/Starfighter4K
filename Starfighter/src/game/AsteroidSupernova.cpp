#include "include/game/AsteroidSupernova.h"
#include "include/engine/GameEngine.h"

AsteroidSupernova::AsteroidSupernova(qreal _dX, qreal _dY,Shooter _from, qreal _dResistance, qreal _dHealthPoint, GameEngine *_gameEngine,qreal _dAngle)
    :Asteroid(_dX,_dY,_from,_dResistance,_dHealthPoint,_gameEngine,1)
{
    dPower = POWER_SUPERNOVA;
    dSpeed = SPEED_SUPERNOVA;
    dAngle = _dAngle;

    numberFrameMin = NB_PICTURE_SUPERNOVA_ASTEROID_MIN;
    numberFrameMax = NB_PICTURE_SUPERNOVA_ASTEROID_MAX;
    currentFrame = _gameEngine->randInt(numberFrameMax-numberFrameMin)+numberFrameMin;

    setPixmap(new QPixmap(QString(PICTURE_SUPERNOVA_ASTEROID).arg(currentFrame)));

    setPos(_dX+_gameEngine->randInt(DELTA_X_SUPERNOVA)-DELTA_X_SUPERNOVA/2,_dY+_gameEngine->randInt(DELTA_Y_SUPERNOVA)-DELTA_Y_SUPERNOVA/2);
}
