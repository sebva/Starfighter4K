/*=====================================================================*
 | Declaration file BonusProjectile.h
 |      declares :  BonusProjectile class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef BONUS_PROJECTILE_H
#define BONUS_PROJECTILE_H

#include "include/game/Bonus.h"

#include "include/enum/Enum.h"

class GameEngine;

class BonusProjectile : public Bonus
{
public:
    BonusProjectile(TypeProjectiles _type, int _expiration, GameEngine *_gameEngine);
    ~BonusProjectile() {}

    TypeProjectiles getType() const {return type;}
    int getExpiration() const {return expiration;}
private:
    TypeProjectiles type;
	int expiration;
};
#endif
