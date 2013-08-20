/*==============================================================*
 | Implementation file BonusProjectile.cpp
 |        implements : BonusProjectile class
 |
 |
 | summary : Entity class that represents a BonusProjectile.
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

#include "include/game/BonusProjectile.h"

BonusProjectile::BonusProjectile(TypeProjectiles _type, int _expiration, GameEngine *_gameEngine)
    :Bonus(_gameEngine),
      type(_type),//Type of the projective offered
      expiration(_expiration)//Time before the expiration (ms)
{
}
