#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "include/enum/Enum.h"

class DisplayEngine;
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
class SpawnEngine;
class QWidget;
class Blackship;
class QKinect;

class GameEngine : public QGraphicsView
{
    Q_OBJECT

public:	
    GameEngine(WiimoteEngine* wiimoteEngine, QKinect* kinect, GameMode gameMode, int duration, SpaceshipType player1Ship, SpaceshipType player2Ship, TypeSpecialBonus sbp1, TypeSpecialBonus sbp2, int difficulty, QWidget*);
    GameEngine(QWidget *parent = 0);
    virtual ~GameEngine();

    static double randDouble();
    static int randInt(int range);

    void createSpaceship();
	int elapsedTime();    
    int timeGamevalue() const {return timeGame;}
    void timerControle(int tps = 15);
	
    virtual qreal xminWarzone() const;
    virtual qreal xmaxWarZone() const;
    virtual QRect sceneSize() const;

    Spaceship * ship1() const {return listSpaceship[0];}
    Spaceship * ship2() const {return listSpaceship[1];}

    SoundEngine* soundEngine() const { return soe;}
    DisplayEngine* displayEngine() const { return de;}
    UserControlsEngine* userControlsEngine() const {return uc;}
    WiimoteEngine* wiimoteEngine() const {return we;}
	SpawnEngine* spawnEngine() const {return se;}
    GameMode getGameMode() const {return gameMode;}

    bool getHasSomeonWon() const {return hasSomeoneWon;}
    virtual void timerEvent(QTimerEvent *);

    virtual void addBlackship(Blackship* _blackship);
    virtual void addProjectile(Projectile *_inProjectile);
    virtual void addSupernova(Supernova *_inSupernova);
    virtual void addShip(Spaceship *_inSpaceship);
    virtual void removeShip(Spaceship *_inSpaceship);
    virtual void addAsteroid(Asteroid *_inAsteroide);
    virtual void removeAsteroid(Asteroid *_inAsteroide);
    virtual void addSmallAsteroid(Asteroid *_inAsteroide);
    virtual void removeSmallAsteroid(Asteroid *_inAsteroide);
    virtual void addBonus(Bonus *_inBonus);
    virtual void addAlienSpaceship(AlienSpaceship *_inAlienSpaceship);
    virtual void removeAlienSpaceship(AlienSpaceship *_inAlienSpaceship);
    virtual void removeBlackship(Blackship* _blackship);
    virtual void removeItemScene(Displayable* item);
    void endGameDeathMatch(Spaceship* _ship=0);
    void endGameTimer();
    virtual void escapeGame(bool isKey = false);

    void enableAntiGravity(Shooter playerActivated);
    void freezePlayer(int duration, Shooter playerDest);

	void quitGame();
signals:
    void endGame();
    void signalPause(bool); // true = isPause

public slots:
    virtual void elemenDestroyed(Destroyable* destroyItem,int nbPoint,Shooter forShip);
	void start();

private slots:
    void rotationProcess(int wiimote, qreal angle);
	void positionProcess();

protected:
    void checkOutsideScene(QList<Displayable*> &list);
    void clearList(QList<Displayable*> &list);
    bool checkCollisionItemAndList(const int i_list1,QList<Displayable*> &list1,QList<Displayable*> &list2);
    bool checkCollisionSpaceshipAndList(const int i_list1,QList<Displayable*> &list);
    void runTestCollision(QList<Displayable*> &list);
    void detectObjectAfterMiddleZone(const QList<Displayable*>& list, QList<Projectile*>& projList, Shooter PlayerActivated);

    QMutex* mutex;
    QList<Displayable*>  listProjectile;
    QList<Displayable*>  listAsteroide;
    QList<Displayable*>  listSmallAsteroide;
    QList<Displayable*>  listBonus;
    QList<Spaceship*>    listSpaceship;
    QList<Displayable*>  listAlienSpaceship;
    QList<Supernova*>    listSupernova;
    QList<Displayable*>  listBlackship;

    SpawnEngine *se;

private:
    SoundEngine *soe;
    DisplayEngine *de;
    UserControlsEngine *uc;
    Settings& settings;
    WiimoteEngine *we;
	QKinect* kinect;

    GameMode gameMode;
    SpaceshipType typeShip1;
    SpaceshipType typeShip2;
    TypeSpecialBonus typeSP1;
    TypeSpecialBonus typeSP2;

    bool isRunning;
    int idTimer;
    bool isTimer;
    int timeGame;
    bool hasSomeoneWon;

    // For elapsedTime()
    QElapsedTimer elapsedTimer;
    qint64 timeAlreadyCounted;
};
#endif
