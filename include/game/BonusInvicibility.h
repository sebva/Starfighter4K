/*=====================================================================*
 | Declaration file BonusSpeed.h
 |      declares :  BonusSpeed class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef BONUS_SPEED_H
#define BONUS_SPEED_H

#include "include/game/Bonus.h"

class GameEngine;

class BonusInvicibility : public Bonus
{
public:
    BonusInvicibility(int _expiration, GameEngine *_gameEngine);
    ~BonusInvicibility() {}

    int getExpiration() const {return expiration;}
private:
	int expiration;
};
#endif
