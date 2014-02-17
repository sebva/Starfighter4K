/*=====================================================================*
 | Declaration file ProjectileAlien.h
 |      declares :  ProjectileAlien class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef PROJECTILE_ALIEN_H
#define PROJECTILE_ALIEN_H

#include "include/game/Projectile.h"
#include "include/config/Define.h"

class ProjectileAlien : public Projectile
{
public:
    ProjectileAlien(qreal _dXOrigin, qreal _dYOrigin,Shooter _from, qreal _dArgument, qreal _dModule);
    ~ProjectileAlien() {}

private:
    static const qreal kIntervalModule;

    void advance(int _step);

    qreal dModule;
};
#endif
