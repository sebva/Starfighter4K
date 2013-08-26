######################################################################
# Automatically generated by qmake (2.01a) ven. 14. déc. 13:08:31 2012
######################################################################

TEMPLATE = app
TARGET = Starfighter4K
PRECOMPILED_HEADER = include\stable.h

DEPENDPATH += . \
              include \
              src \
              include\engine \
              include\enum \
              include\game \
              include\menu \
              include\utils \
              res\ui \
              src\engine \
              src\game \
              src\menu \
              src\utils
INCLUDEPATH += .

# Input
HEADERS += include/stable.h \
           include/engine/DisplayEngine.h \
           include/engine/GameEngine.h \
           include/engine/SoundEngine.h \
           include/engine/SpawnEngine.h \
           include/engine/UserControlsEngine.h \
           include/enum/Enum.h \
           include/game/AlienSpaceship.h \
           include/game/Asteroid.h \
           include/game/Bonus.h \
           include/game/BonusForceField.h \
           include/game/BonusHP.h \
           include/game/BonusProjectile.h \
           include/game/Destroyable.h \
           include/game/Displayable.h \
           include/game/Projectile.h \
           include/game/ProjectileAlien.h \
           include/game/ProjectileCross.h \
           include/game/ProjectileSimple.h \
           include/game/ProjectileV.h \
           include/game/Spaceship.h \
           include/game/Supernova.h \
           include/menu/AboutDialog.h \
           include/menu/MainDialog.h \
           include/menu/NewGameDialog.h \
           include/menu/OptionsDialog.h \
           include/utils/Settings.h \
    include/config/Define.h \
    include/game/AsteroidSupernova.h \
    include/engine/WiimoteEngine.h \
    include/game/BonusInvicibility.h \
    include/game/SpecialBonus.h \
    include/game/SpecialBonusFreeze.h \
    include/game/SpecialBonusLimitedTime.h \
    include/menu/HUDWidget.h \
    include/game/SpecialBonusLimitedUsage.h \
    include/game/SpecialBonusAntiGravity.h \
    include/game/ProjectileTracking.h \
    include/game/SpecialBonusTracking.h \
    include/game/ProjectileMulti.h \
    include/game/SpecialBonusMulti.h \
    include/game/ProjectileGuided.h \
    include/game/SpecialBonusGuided.h \
    include/menu/BonusWidget.h
FORMS += res/ui/AboutDialog.ui \
         res/ui/MainDialog.ui \
         res/ui/NewGameDialog.ui \
         res/ui/OptionsDialog.ui \
	 res/ui/HUDWidget.ui
SOURCES += src/main.cpp \
           src/engine/DisplayEngine.cpp \
           src/engine/GameEngine.cpp \
           src/engine/SoundEngine.cpp \
           src/engine/SpawnEngine.cpp \
           src/engine/UserControlsEngine.cpp \
           src/game/AlienSpaceship.cpp \
           src/game/Asteroid.cpp \
           src/game/Bonus.cpp \
           src/game/BonusForceField.cpp \
           src/game/BonusHP.cpp \
           src/game/BonusProjectile.cpp \
           src/game/Destroyable.cpp \
           src/game/Displayable.cpp \
           src/game/Projectile.cpp \
           src/game/ProjectileAlien.cpp \
           src/game/ProjectileCross.cpp \
           src/game/ProjectileSimple.cpp \
           src/game/ProjectileV.cpp \
           src/game/Spaceship.cpp \
           src/game/Supernova.cpp \
           src/menu/AboutDialog.cpp \
           src/menu/MainDialog.cpp \
           src/menu/NewGameDialog.cpp \
           src/menu/OptionsDialog.cpp \
           src/utils/Settings.cpp \
    src/engine/WiimoteEngine.cpp \
    src/game/BonusInvicibility.cpp \
    src/game/SpecialBonusFreeze.cpp \
    src/game/SpecialBonusLimitedTime.cpp \
   src/menu/HUDWidget.cpp \
    src/game/AsteroidSupernova.cpp \
    src/menu/BonusWidget.cpp \
    src/game/SpecialBonusLimitedUsage.cpp \
    src/game/SpecialBonusAntiGravity.cpp \
    src/game/ProjectileTracking.cpp \
    src/game/SpecialBonusTracking.cpp \
    src/game/ProjectileMulti.cpp \
    src/game/SpecialBonusMulti.cpp \
    src/game/ProjectileGuided.cpp \
    src/game/SpecialBonusGuided.cpp

RESOURCES += ressources.qrc
RC_FILE = icon.rc
TRANSLATIONS += starfighter4K_fr.ts
QT += opengl widgets multimedia gui
LIBS += "./lib/wiiuse/wiiuse.lib" -Llib/wiiuse/ -lwiiuse
#QMAKE_CXXFLAGS += -std=c++11

# if you are using Shadow build, you need to get the output folder
CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

sounds.path = $$DESTDIR/sounds
sounds.files += $$files(res/sounds/*)

INSTALLS += sounds
