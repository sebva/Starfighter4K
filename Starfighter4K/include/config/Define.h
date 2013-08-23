#ifndef DEFINE_H
#define DEFINE_H

#include "include/enum/Enum.h"

//Modifiable

//DisplayEngine
#define BACKGROUND                          ":/images/game/background"
#define ICON_TASKBAR                        ":/images/taskbar-icon"

//SpawnEngine
#define PROB_ASTEROID                       75
#define PROB_ALIEN                          25
#define PROB_SAT                            15
#define PROB_SUPERNOVA                      1

#define SPAWN_INTERVAL                      250 // (ms)
#define RESISTANCE_ASTEROID                 50
#define RESISTANCE_ALIEN                    425
#define ALIEN_SWIRL_MIN                     10
#define ALIEN_SWIRL_MAX                     20
#define BONUS_HEALTH_MIN                    15
#define BONUS_HEALTH_MAX                    45
#define MAX_SPACESHIP_PV                    100
#define BONUS_PROJECTILE_DURATION           10000       // (ms)
#define BONUS_TYPE_PROJECTILES_MIN          2           // ProjCross
#define BONUS_TYPE_PROJECTILES_MAX          3           //ProjV
#define BONUS_INVICIBILITY_DURATION                5000        // (ms)

//UserControlsEngine
#define REFRESH                             17 // (ms)
#define NOVATIMER                           10000 // (ms)

//AlienSpaceShip
#define PICTURE_ALIENSPACESHIP              ":/images/game/mothership"
#define ARG_INCREMENTATION_ALIENSPACESHIP   0.0005 // rad

//Asteroid
#define SPEED_ASTEROID                      3 //Factor
#define SPEED_SMALL_ASTEROID                3 //Factor, keep the same than SPEED_ASTEROID
#define MAX_ASTEROID                        5 //Number max of small asteroids
#define MIN_ASTEROID                        3 //Number min of small asteroids
#define DELTA_ANGLE_BETWEEN_180_AXES        M_PI/3

#define POWER_ASTEROID                      5000
#define POWER_SMALL_ASTEROID                2500
#define RESISTANCE_SMALL_ASTEROID           1 // Min : 1 Max : 100
#define HEALTHPOINT_SMALL_ASTEROID          50

#define NUMBER_FRAME_BEFORE_CHANGING_PIC    2

#define PICTURE_ASTEROID                    ":/images/game/asteroids/rock%1"
#define NB_PICTURE_ASTEROID_MIN             10000
#define NB_PICTURE_ASTEROID_MAX             10031

#define PICTURE_SMALL_ASTEROID              ":/images/game/asteroids/rock%1"
#define NB_PICTURE_SMALL_ASTEROID_MIN       20000
#define NB_PICTURE_SMALL_ASTEROID_MAX       20031

#define PICTURE_SUPERNOVA_ASTEROID          ":/images/game/asteroids/rock%1"
#define NB_PICTURE_SUPERNOVA_ASTEROID_MIN   30000
#define NB_PICTURE_SUPERNOVA_ASTEROID_MAX   30031

//Bonus
#define SOUND_TIMER                         500 // (ms)
#define PICTURE_BONUS                       ":/images/game/bonus"
#define ARG_INCREMENTATION_BONUS            0.0060 // rad

//Projectile
#define RADIUS_PROJECTILE                   10 // px

//Point
#define NB_POINT_PROJECTILE                 20 //When a spaceship touchs another one
#define NB_POINT_SMALL_ASTEROID             25 // small
#define NB_POINT_ASTEROID                   50 // big
#define NB_POINT_ALIENSPACESHIP             250
#define NB_POINT_BONUS                      100

//ProjectileAlien
#define POWER_ALIEN                         5500
#define MODULE_INCREMENT_ALIEN              4.0

//ProjectileCross
#define POWER_CROSS                         750
#define SPEED_CROSS_DEF                     25 // dx
#define SLOPE_CROSS                         M_PI/16

//ProjectileSimple
#define POWER_SIMPLE                        1000
#define SPEED_SIMPLE_DEF                    25 // dx

//ProjectileV
#define POWER_V                             750
#define SPEED_V_DEF                         25 // dx

//ProjectileTracking
#define POWER_TRACKING                      10000
#define SPEED_TRACKING_DEF                  20

//ProjectileMulti
#define POWER_MULTI                         1000
#define SPEED_MULTI_DEF                     25

//Spaceship
//PV -> cf SpawnEngine
#define MAX_SPACESHIP_BONUS                 2
#define AMPLI_SPACESHIP_PROJ_V              60.0 //px
#define OMEGA_SPACESHIP_PROJ_V              0.020 // rad/s
#define PROJ_SPACESHIP_DEF                  ProjSimple
#define RESISTANCE_FORCE_FIELD              100

#define PICTURE_SPACESHIP_1                 ":/images/game/ship1"
#define PICTURE_SPACESHIP_2                 ":/images/game/ship2"
#define PICTURE_SPACESHIP_3                 ":/images/game/ship3"
#define HEALTHPOINT_1                       100
#define HEALTHPOINT_2                       100
#define HEALTHPOINT_3                       100
#define RESISTANCE_1                        100
#define RESISTANCE_2                        75
#define RESISTANCE_3                        150
#define SPEED_1                             8 // dy
#define SPEED_2                             9 // dy
#define SPEED_3                             5

//Supernova
#define NB_SPIRAL                           45
#define POWER_SUPERNOVA                     7500
#define SPEED_SUPERNOVA                     5
#define DELTA_X_SUPERNOVA                   100
#define DELTA_Y_SUPERNOVA                   100

//Do not touch

//DisplayEngine
#define SPACE_BETWEEN                       250
#define SPACE_INPLAYER                      50

//Sounds
#define SOUNDS_DIR                          "./sounds/" // Trailing slash mandatory
#define MENU_MUSIC                          "menu.mp3"
#define GAME_MUSIC                          "game.mp3"
#define SHOOT_SOUND                         "laser.mp3"
#define SAT_SOUND                           "beep.mp3"
#define SUPERNOVA_SOUND                     "supernova.mp3"

//HUD
#define IMAGE_BONUS_FREEZE          ":/images/bonus/freeze"
#define IMAGE_BONUS_INVICIBILITY    ":/images/bonus/invicibility"
#define IMAGE_BONUS_HEALTH          ":/images/bonus/medic"
#define IMAGE_BONUS_PROJ_CROSS      ":/images/bonus/projCross"
#define IMAGE_BONUS_PROJ_SIMPLE     ":/images/bonus/projSimple"
#define IMAGE_BONUS_PROJ_V          ":/images/bonus/projV"
#define IMAGE_BONUS_SHIELD          ":/images/bonus/shield"
#define IMAGE_BONUS                 ":/images/bonus/bonus"

//AlienSpaceShip
#define MARGIN_Y                            10
#define DELTA_X_MIN                         50
#define DELTA_X                             200 //Cf Specification file

//Bonus
#define DELTA_X_B                           100 //Cf Specification file

//Wiimote
#define RUMBLE_TIME                         200

#endif // DEFINE_H
