/*=====================================================================*
 | Declaration file BonusHP.h
 |      declares :  BonusHP class
 |
 | For more informations (creation date, creator, etc.), please see the
 | corresponding .cpp file
 |
 *=====================================================================*/

#ifndef BONUS_H_P_H
#define BONUS_H_P_H

#include "include/game/Bonus.h"

class GameEngine;

class BonusHP : public Bonus
{
public:
    BonusHP(qreal _dHealthPoint, GameEngine *_gameEngine);
    ~BonusHP() {}
    qreal getHealthPoint() const {return dHealthPoint;}
private:
    qreal dHealthPoint;
};
#endif
