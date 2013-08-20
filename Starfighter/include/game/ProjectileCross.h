/*=====================================================================*
 | Declaration file ProjectileCross.h
 |      declares :  ProjectileCross class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef PROJECTILE_CROSS_H
#define PROJECTILE_CROSS_H

#include "include/game/Projectile.h"

class ProjectileCross : public Projectile
{
public:
    ProjectileCross(qreal _dXOrigin, qreal _dYOrigin,Shooter _from,int _nb);
    ~ProjectileCross() {}

};
#endif
