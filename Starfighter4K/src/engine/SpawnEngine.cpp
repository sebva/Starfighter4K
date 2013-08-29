#include "include/engine/SpawnEngine.h"
#include "include/engine/GameEngine.h"
#include "include/engine/DisplayEngine.h"

#include "include/game/Asteroid.h"
#include "include/game/AlienSpaceship.h"
#include "include/game/BonusForceField.h"
#include "include/game/BonusHP.h"
#include "include/game/BonusProjectile.h"
#include "include/game/BonusInvicibility.h"
#include "include/game/Supernova.h"
#include "include/game/Spaceship.h"

#define arccot M_PI / 2.0 - atan

SpawnEngine::SpawnEngine(int difficulty, GameEngine *_ge, bool _isDemo):isDemo(_isDemo)
{
    this->ge = _ge;
    this->de = _ge->displayEngine();

    spawnAsteroids = (bool)(difficulty & Asteroids);
    spawnAlienMothership = (bool)(difficulty & AlienMothership);
    spawnSatellites = (bool)(difficulty & Satellites);
    spawnSupernovae = (bool)(difficulty & Supernovae);

    totalProba = spawnAsteroids ? kProbAsteroid : 0;
    totalProba += spawnAlienMothership ? (isDemo ? PROB_ALIEN_DEMO : kProbAlien) : 0;
    totalProba += spawnSatellites ? kProbSat : 0;
    totalProba += spawnSupernovae ? kProbSupernova : 0;

    intervalAsteroid = spawnAsteroids ? kProbAsteroid : 0;
    intervalAlien = spawnAlienMothership ? intervalAsteroid + (isDemo ? kProbAlien : PROB_ALIEN_DEMO ): intervalAsteroid;
    intervalSat = spawnSatellites ? intervalAlien + kProbSat : intervalAlien;
    intervalSupernova = spawnSupernovae ? intervalSat + kProbSupernova : intervalSat;

    timer = new QTimer(this);
    timer->setInterval(SPAWN_INTERVAL);

    connect(ge, SIGNAL(signalPause(bool)), this, SLOT(pause(bool)));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerFired()));

    timer->start();
}

SpawnEngine::~SpawnEngine()
{
    delete timer;

    //GameEngine delete DisplayEngine and SpawnEngine
}

void SpawnEngine::timerFired()
{
    double probSpawn = (isDemo) ? 0.5 : proba(ge->elapsedTime() / 1000.0);

    if(ge->randDouble() < probSpawn)
    {
        int probWhat = ge->randInt(totalProba);

        if(probWhat < intervalAsteroid)
        {
            Asteroid *asteroid = new Asteroid(0, 0, Other, RESISTANCE_ASTEROID, MAX_SPACESHIP_PV, ge);
            ge->addAsteroid(asteroid);
        }
        else if(probWhat < intervalAlien)
        {
            int nbSpirales = irand(ALIEN_SWIRL_MIN, ALIEN_SWIRL_MAX);
            AlienSpaceship *alien = new AlienSpaceship(nbSpirales, MAX_SPACESHIP_PV, RESISTANCE_ALIEN, ge);
            ge->addAlienSpaceship(alien);
        }
        else if(probWhat < intervalSat)
        {
            ge->addBonus(generateBonus());
        }
        else if(probWhat < intervalSupernova)
        {
            Supernova *supernova = new Supernova(ge->sceneSize().width() / 2, ge->sceneSize().height() / 2, ge);
            ge->addSupernova(supernova);
        }
    }
}

Bonus* SpawnEngine::generateBonus()
{
    int satType = irand(1, 5);
    Bonus *bonus=0;

    switch(satType)
    {
    case 1:
        bonus = new BonusForceField(ge);
        break;
    case 2:
        bonus = new BonusHP(irand(BONUS_HEALTH_MIN, BONUS_HEALTH_MAX), ge);
        break;
    case 3:
    case 4:
        bonus = new BonusProjectile((TypeProjectiles)irand(BONUS_TYPE_PROJECTILES_MIN, BONUS_TYPE_PROJECTILES_MAX), BONUS_PROJECTILE_DURATION, ge);
        break;
    case 5:
        bonus = new BonusInvicibility(BONUS_INVICIBILITY_DURATION, ge);
        break;
    }

    return bonus;
}

void SpawnEngine::pause(bool isPause)
{
    if(isPause)
        timer->stop();
    else
        timer->start();
}

int SpawnEngine::irand(int min, int max)
{
    return GameEngine::randInt(max - min) + min;
}

double SpawnEngine::proba(double t)
{
    return 0.15 + ((arccot(30.0 * t + 100.0)) * 100.0) + t/600.0 + (0.4 * sin(t/20.0) * 0.5 * cos(t/9.0 + 5));
}
