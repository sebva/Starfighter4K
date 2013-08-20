/*==============================================================*
 | Implementation file BonusSpeed.cpp
 |        implements : BonusSpeed class
 |
 |
 | summary : Entity class that represents a BonusSpeed.
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

#include "include/game/BonusSpeed.h"

BonusSpeed::BonusSpeed(qreal _dSpeed, int _expiration, GameEngine *_gameEngine)
    :Bonus(_gameEngine),
      dSpeed(_dSpeed),//Speed bonus
      expiration(_expiration)//Time before expiration of the bonus (ms)
{

}
