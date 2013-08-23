/*==============================================================*
 | Implementation file BonusHP.cpp
 |        implements : BonusHP class
 |
 |
 | summary : Entity class that represents a BonusHP (HealthPoint).
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

#include "include/game/BonusHP.h"

BonusHP::BonusHP(qreal _dHealthPoint, GameEngine *_gameEngine)
    :Bonus(TypeBonusHP, _gameEngine),
      dHealthPoint(_dHealthPoint)//Number of HP offered
{

}
