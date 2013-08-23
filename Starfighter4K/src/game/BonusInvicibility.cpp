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

#include "include/game/BonusInvicibility.h"
#include "include/engine/GameEngine.h"

BonusInvicibility::BonusInvicibility(int _expiration, GameEngine *_gameEngine)
    :Bonus(TypeBonusInvicibility, _gameEngine),
      expiration(_expiration)//Time before expiration of the bonus (ms)
{

}
