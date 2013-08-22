/*=====================================================================*
 | Declaration file ProjectileV.h
 |      declares :  ProjectileV class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef PROJECTILE_V_H
#define PROJECTILE_V_H

#include "include/game/Projectile.h"

class ProjectileV : public Projectile
{
public:
    ProjectileV(qreal _dXOrigin, qreal _dYOrigin, Shooter _from, qreal _dAmpli, qreal _dOmega, qreal _dAngle);
    ~ProjectileV() {}

private:
    void advance(int _step);
    qreal dAmplitude;
    qreal dOmega;
    qreal dAngle2;
};
#endif
