#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "include/enum/Enum.h"

class DisplayEngine;
class SpawnEngine;
class UserControlsEngine;
class SoundEngine;
class Projectile;
class Supernova;
class Spaceship;
class Asteroid;
class Bonus;
class AlienSpaceship;
class Destroyable;
class Displayable;
class Settings;
class QMutex;
class WiimoteEngine;

class GameEngine : public QObject
{
    Q_OBJECT

public:	
    GameEngine(WiimoteEngine* wiimoteEngine, GameMode gameMode, int duration, SpaceshipType player1Ship, SpaceshipType player2Ship, int difficulty, QObject*);
    ~GameEngine();

    static double randDouble();
    static int randInt(int range);

    void createSpaceship();
	int elapsedTime();    
    int timeGamevalue() const {return timeGame;}
    void timerControle(int tps = 15);

    Spaceship * ship1() const {return listSpaceship[0];}
    Spaceship * ship2() const {return listSpaceship[1];}

    SoundEngine* soundEngine() const { return soe;}
    DisplayEngine* displayEngine() const { return de;}
    UserControlsEngine* userControlsEngine() const {return uc;}
    WiimoteEngine* wiimoteEngine() const {return we;}
    GameMode getGameMode() const {return gameMode;}

    bool getHasSomeonWon() const {return hasSomeoneWon;}
    void timerEvent(QTimerEvent *);

    void addProjectile(Projectile *_inProjectile);
    void addSupernova(Supernova *_inSupernova);
    void addShip(Spaceship *_inSpaceship);
    void removeShip(Spaceship *_inSpaceship);
    void addAsteroid(Asteroid *_inAsteroide);
    void removeAsteroid(Asteroid *_inAsteroide);
    void addSmallAsteroid(Asteroid *_inAsteroide);
    void removeSmallAsteroid(Asteroid *_inAsteroide);
    void addBonus(Bonus *_inBonus);
    void addAlienSpaceship(AlienSpaceship *_inAlienSpaceship);
    void removeAlienSpaceship(AlienSpaceship *_inAlienSpaceship);

    void endGameDeathMatch(Spaceship* _ship=0);
    void endGameTimer();
    void escapeGame();

    void enableAntiGravity(Shooter playerActivated);
    void freezePlayer(int duration, Shooter playerDest);

signals:
    void endGame();
    void signalPause(bool); // true = isPause

public slots:
    void elemenDestroyed(Destroyable* destroyItem,int nbPoint,Shooter forShip);

private slots:
    void rotationProcess(int wiimote, qreal angle);

private:
    void checkOutsideScene(QList<Displayable*> &list);
    void clearList(QList<Displayable*> &list);
    bool checkCollisionItemAndList(const int i_list1,QList<Displayable*> &list1,QList<Displayable*> &list2);
    bool checkCollisionSpaceshipAndList(const int i_list1,QList<Displayable*> &list);
    void runTestCollision(QList<Displayable*> &list);
    void detectObjectAfterMiddleZone(const QList<Displayable*>& list, QList<Projectile*>& projList, Shooter PlayerActivated);

    SoundEngine *soe;
    DisplayEngine *de;
    SpawnEngine *se;
    UserControlsEngine *uc;
    Settings& settings;
    WiimoteEngine *we;

    GameMode gameMode;
    SpaceshipType typeShip1;
    SpaceshipType typeShip2;

    QMutex* mutex;

    bool isRunning;
    int idTimer;
    bool isTimer;
    int timeGame;
    bool hasSomeoneWon;

    // For elapsedTime()
    QElapsedTimer elapsedTimer;
    qint64 timeAlreadyCounted;

    QList<Displayable*>  listProjectile;
    QList<Displayable*>  listAsteroide;
    QList<Displayable*>  listSmallAsteroide;
    QList<Displayable*>  listBonus;
    QList<Spaceship*>    listSpaceship;
    QList<Displayable*>  listAlienSpaceship;
    QList<Supernova*>    listSupernova;


};
#endif
