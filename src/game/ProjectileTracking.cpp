#include "include/game/ProjectileTracking.h"
#include "include/engine/GameEngine.h"
#include "include/engine/SoundEngine.h"
#include "include/game/Spaceship.h"
#include "include/config/Define.h"

ProjectileTracking::ProjectileTracking(qreal _dXOrigin, qreal _dYOrigin,Shooter _from, Spaceship* _playerFront, GameEngine* _ge)
    :Projectile(_dXOrigin, _dYOrigin, _from),spaceship(_playerFront),ge(_ge)
{
    dOriginAngle = dAngle;
    dSpeed = SPEED_TRACKING_DEF;
    dPower = POWER_TRACKING;

    loadPixmap();
}

void ProjectileTracking::advance(int _step)
{
    qreal x = spaceship->getXPositionCenter();
    qreal y = spaceship->getYPositionFire();

    dAngle = dOriginAngle - cos(dAngle)*atan((y-pos().y())/abs(x-pos().x()));
    loadPixmap();

    Projectile::advance(_step);
}

ProjectileTracking::~ProjectileTracking()
{
	ge->soundEngine()->stopSound(TrackingSound);
}