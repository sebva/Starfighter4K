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

class BonusSpeed : public Bonus
{
public:
    BonusSpeed(qreal _dSpeed, int _expiration, GameEngine *_gameEngine);
    ~BonusSpeed() {}

    qreal getSpeed() const {return dSpeed;}
    int getExpiration() const {return expiration;}
private:
    qreal dSpeed;
	int expiration;
};
#endif
