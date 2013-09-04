#ifndef DEFINE_H
#define DEFINE_H

#include "include/enum/Enum.h"

//Modifiable

#define NAMES								"Sébastien Vaucher" << "Alexandre Perez" << "Diego Antognini"

//DisplayEngine
#define BACKGROUND                          ":/images/game/background"
#define BACKGROUND_DX                       0.25
#define BACKGROUND_DY                       0.25
#define ICON_TASKBAR                        ":/images/taskbar-icon"
#define FONT_PATH							":/font/HelveticaNeueLight.ttf"
#define NB_COUNTDOWN						3

//SpawnEngine
#define PROB_ASTEROID                       75
#define PROB_ALIEN                          25
#define PROB_ALIEN_DEMO                     10
#define PROB_SAT                            15
#define PROB_SUPERNOVA                      3
#define PROB_BLACKSQUADRON                  5

#define SPAWN_INTERVAL                      400 // (ms)
#define RESISTANCE_ASTEROID                 50
#define RESISTANCE_ALIEN                    425
#define ALIEN_SWIRL_MIN                     20
#define ALIEN_SWIRL_MAX                     30
#define BONUS_HEALTH_MIN                    30
#define BONUS_HEALTH_MAX                    70
#define MAX_SPACESHIP_PV                    100
#define BONUS_PROJECTILE_DURATION           8000       // (ms)
#define BONUS_TYPE_PROJECTILES_MIN          2           // ProjCross
#define BONUS_TYPE_PROJECTILES_MAX          3           //ProjV
#define BONUS_INVICIBILITY_DURATION         5000        // (ms)

//UserControlsEngine
#define REFRESH                             17 // (ms)
#define NOVATIMER                           10000 // (ms)

//AlienSpaceShip
#define PICTURE_ALIENSPACESHIP              ":/images/game/mothership"
#define PICTURE_ALIENSPACESHIP_SHADOW       ":/images/game/shadow"
#define ARG_INCREMENTATION_ALIENSPACESHIP   0.0010 // rad

//Asteroid
#define SPEED_ASTEROID                      3 //Factor
#define SPEED_SMALL_ASTEROID                3 //Factor, keep the same than SPEED_ASTEROID
#define MAX_ASTEROID                        5 //Number max of small asteroids
#define MIN_ASTEROID                        3 //Number min of small asteroids
#define DELTA_ANGLE_BETWEEN_180_AXES        M_PI/3

#define POWER_ASTEROID                      1
#define POWER_SMALL_ASTEROID                1500
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

//Point
#define NB_POINT_PROJECTILE                 20 //When a spaceship touchs another one
#define NB_POINT_SMALL_ASTEROID             25 // small
#define NB_POINT_ASTEROID                   50 // big
#define NB_POINT_ALIENSPACESHIP             250
#define NB_POINT_BONUS                      100
#define NB_POINT_BLACKSHIP                  150

//ProjectileAlien
#define POWER_ALIEN                         3500
#define MODULE_INCREMENT_ALIEN              4.0

//ProjectileCross
#define POWER_CROSS                         600
#define SPEED_CROSS_DEF                     25 // dx
#define SLOPE_CROSS                         M_PI/16

//ProjectileSimple
#define POWER_SIMPLE                        1000
#define SPEED_SIMPLE_DEF                    25 // dx

//ProjectileV
#define POWER_V                             1250
#define SPEED_V_DEF                         25 // dx

//ProjectileTracking
#define POWER_TRACKING                      5000
#define SPEED_TRACKING_DEF                  20

//ProjectileMulti
#define POWER_MULTI                         800
#define SPEED_MULTI_DEF                     25

//ProjectileGuided
#define POWER_GUIDED                        1000000
#define SPEED_GUIDED_DEF                    15

//AntiGravity
#define SPEED_FACTOR_ANTI_GRAVITY           1.5

//Spaceship
//PV -> cf SpawnEngine
#define AMPLI_SPACESHIP_PROJ_V              60.0 //px
#define OMEGA_SPACESHIP_PROJ_V              0.020 // rad/s
#define PROJ_SPACESHIP_DEF                  ProjSimple
#define RESISTANCE_FORCE_FIELD              100
#define PICTURE_PROJ_SPACESHIP_1            ":/images/game/proj1"
#define PICTURE_PROJ_SPACESHIP_2            ":/images/game/proj2"
#define PICTURE_PROJ_SPACESHIP_3            ":/images/game/proj3"
#define PICTURE_PROJ_GUIDED                 ":/images/game/proj4"

#define PICTURE_SPACESHIP_1                 ":/images/game/ship1"
#define PICTURE_SPACESHIP_2                 ":/images/game/ship2"
#define PICTURE_SPACESHIP_3                 ":/images/game/ship3"
#define PICTURE_SHIELD                      ":/images/game/shield"
#define HEALTHPOINT_1                       100
#define HEALTHPOINT_2                       100
#define HEALTHPOINT_3                       100
#define RESISTANCE_1                        200
#define RESISTANCE_2                        150
#define RESISTANCE_3                        300
#define COOLDOWN_1                          11000 // ms
#define COOLDOWN_2                          8000 // ms
#define COOLDOWN_3                          15000 // ms

//Supernova
#define NB_SPIRAL                           45
#define POWER_SUPERNOVA                     7500
#define SPEED_SUPERNOVA                     5
#define DELTA_X_SUPERNOVA                   100
#define DELTA_Y_SUPERNOVA                   100

//BlackShip
#define PICTURE_BLACKSHIP                   ":/images/game/blackship"
#define POWER_BLACKSHIP_PROJECTILE          500
#define SPEED_BLACKSHIP_PROJECTILE          30
#define INTERVAL_ATTACK_DISTANCE_BLACKSHIP  8
#define ANGLE_FIRST_BLACKSHIP_FIRE          20*M_PI/180.0
#define ANGLE_SECOND_BLACKSHIP_FIRE         10*M_PI/180.0
#define ANGLE_THIRD_BLACKSHIP_FIRE          0*M_PI/180.0
#define SPEED_BLACKSHIP                     4
#define RESISTANCE_BLACKSHIP                25
#define PICTURE_PROJ_BLACKSHIP              ":/images/game/projblack"
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
#define TRACKING_SOUND						"tracking.mp3"
#define FREEZE_SOUND						"freeze.mp3"
#define ANTIGRAVITY_SOUND					"antigravity.mp3"

//HUD
#define IMAGE_BONUS_ANTIGRAVITY     ":/images/bonus/antiGravity"
#define IMAGE_BONUS_ROOTSHOT        ":/images/bonus/projRoot"
#define IMAGE_BONUS_FREEZE          ":/images/bonus/freeze"
#define IMAGE_BONUS_INVICIBILITY    ":/images/bonus/invicibility"
#define IMAGE_BONUS_HEALTH          ":/images/bonus/medic"
#define IMAGE_BONUS_PROJ_CROSS      ":/images/bonus/projCross"
#define IMAGE_BONUS_PROJ_SIMPLE     ":/images/bonus/projSimple"
#define IMAGE_BONUS_PROJ_V          ":/images/bonus/projV"
#define IMAGE_BONUS_SHIELD          ":/images/bonus/shield"
#define IMAGE_BONUS_GUIDEDMISSILE   ":/images/bonus/guided"
#define IMAGE_BONUS_TRACKINGMISSILE ":/images/bonus/tracking"
#define IMAGE_BONUS                 ":/images/bonus/bonus"

#define HUD_BONUS_ACTIVATED_COLOR   QColor(0, 0, 255, 127)
#define HUD_BONUS_COOLDOWN_COLOR    QColor(0, 0, 0, 127)

//AlienSpaceShip
#define MARGIN_Y                            10
#define MARGIN_Y_FIRE                       100
#define DELTA_X_MIN                         50
#define DELTA_X                             200 //Cf Specification file

//Bonus
#define DELTA_X_B                           100 //Cf Specification file
#define ANTIGRAVITY_ACTIVATIONS             1
#define FREEZE_DURATION                     2000
#define GUIDED_ACTIVATIONS                  1
#define ROOTSHOT_ACTIVATIONS                6
#define TRACKING_ACTIVATIONS                1

//Wiimote
#define RUMBLE_TIME                         200

#endif // DEFINE_H
