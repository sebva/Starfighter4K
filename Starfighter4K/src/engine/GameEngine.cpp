#include "include/engine/GameEngine.h"
#include "include/engine/DisplayEngine.h"
#include "include/engine/SpawnEngine.h"
#include "include/engine/UserControlsEngine.h"
#include "include/engine/SoundEngine.h"

#include "include/game/Spaceship.h"
#include "include/game/Destroyable.h"
#include "include/game/AlienSpaceship.h"
#include "include/game/Asteroid.h"
#include "include/game/BonusForceField.h"
#include "include/game/BonusHP.h"
#include "include/game/BonusProjectile.h"
#include "include/game/BonusInvicibility.h"
#include "include/game/Supernova.h"
#include "include/game/BlackShip.h"

#include "include/utils/Settings.h"
#include "include/config/Define.h"

#include "include/engine/WiimoteEngine.h"
#include "include/kinect/qkinect.h"

GameEngine::GameEngine(WiimoteEngine* wiimoteEngine, QKinect* kinect, GameMode gameMode, int duration, SpaceshipType player1Ship, SpaceshipType player2Ship, TypeSpecialBonus sbp1, TypeSpecialBonus sbp2, int difficulty, QWidget *parent = 0)
	:QGraphicsView(parent),we(wiimoteEngine), kinect(kinect),
      settings(Settings::getGlobalSettings()),gameMode(gameMode),typeShip1(player1Ship),typeShip2(player2Ship),
      isRunning(false),idTimer(-1),isTimer(false),timeGame(duration),hasSomeoneWon(false),timeAlreadyCounted(0),typeSP1(sbp1), typeSP2(sbp2)
{
    if(this->gameMode==Timer)
        isTimer=true;

    soe = new SoundEngine(settings.soundEffectsVolume(), settings.musicVolume(), this);
    de = new DisplayEngine(this,0);
    uc = new UserControlsEngine(this, we);
    se = new SpawnEngine(difficulty, this);
	se->pause(true);
    mutex = new QMutex();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    createSpaceship();  

	de->startCountDown();

	connect(kinect, SIGNAL(newDatas()), this, SLOT(positionProcess()));
    connect(we,SIGNAL(orientation(int, qreal)), this, SLOT(rotationProcess(int, qreal)));
}

GameEngine::GameEngine(QWidget *parent)
    :QGraphicsView(parent),settings(Settings::getGlobalSettings())
{
    se = new SpawnEngine(Asteroids|AlienMothership|Satellites|BlackSquadron,this,true);
    mutex = new QMutex();
    de = 0;
    uc = 0;
    soe = 0;
}

GameEngine::~GameEngine()
{
    if(de != 0) delete de;//Delete all the pointers in the different QList, so we must only clear them
    if(uc != 0) delete uc;
    if(se != 0) delete se;
    if(soe != 0) delete soe;
    if(mutex != 0) delete mutex;

    listProjectile.clear();
    listAsteroide.clear();
    listSmallAsteroide.clear();
    listBonus.clear();
    listSpaceship.clear();
    listAlienSpaceship.clear();
    listSupernova.clear();
	listBlackship.clear();
}

qreal GameEngine::xminWarzone() const
{
    return de->xminWarzone();
}

qreal GameEngine::xmaxWarZone() const
{
    return de->xmaxWarZone();
}

QRect GameEngine::sceneSize() const
{
    return de->sceneSize();
}

double GameEngine::randDouble()
{
    return (double)qrand() / (double)RAND_MAX;
}

int GameEngine::randInt(int range)
{
    if(range == 0)
        return 0;
    else
        return qrand() % (range+1);
}

void GameEngine::createSpaceship()
{
    int width = de->sceneSize().width();
    int height = de->sceneSize().height();

    qreal healthPoint = 0;
    qreal resistance = 0;
    int cooldown = 0;
    QString path;
    if(typeShip1==SpaceshipType1)
    {
        healthPoint = HEALTHPOINT_1;
        resistance = RESISTANCE_1;
        path = QString(PICTURE_SPACESHIP_1);
        cooldown = COOLDOWN_1;
    }
    else if(typeShip1==SpaceshipType2)
    {
        healthPoint = HEALTHPOINT_2;
        resistance = RESISTANCE_2;
        path = QString(PICTURE_SPACESHIP_2);
        cooldown = COOLDOWN_2;
    }
    else if(typeShip1==SpaceshipType3)
    {
        healthPoint = HEALTHPOINT_3;
        resistance = RESISTANCE_3;
        path = QString(PICTURE_SPACESHIP_3);
        cooldown = COOLDOWN_3;
    }
    addShip(new Spaceship(0,height/2,Player1,settings.playerOneName(),healthPoint,resistance,cooldown,typeSP1,this));
    listSpaceship[0]->setPixmap(new QPixmap(path));

    if(typeShip2==SpaceshipType1)
    {
        healthPoint = HEALTHPOINT_1;
        resistance = RESISTANCE_1;
        path = QString(PICTURE_SPACESHIP_1);
        cooldown = COOLDOWN_1;
    }
    else if(typeShip2==SpaceshipType2)
    {
        healthPoint = HEALTHPOINT_2;
        resistance = RESISTANCE_2;
        path = QString(PICTURE_SPACESHIP_2);
        cooldown = COOLDOWN_2;
    }
    else if(typeShip2==SpaceshipType3)
    {
        healthPoint = HEALTHPOINT_3;
        resistance = RESISTANCE_3;
        path = QString(PICTURE_SPACESHIP_3);
        cooldown = COOLDOWN_3;
    }
    addShip(new Spaceship(width,height/2,Player2,settings.playerTwoName(),healthPoint,resistance,cooldown,typeSP2,this));
    listSpaceship[1]->setPixmap(new QPixmap(path));
}

void GameEngine::start()
{
	uc->start();
	timerControle();
	elapsedTimer.start();
}

void GameEngine::timerEvent(QTimerEvent *)
{
    de->moveBG();
    de->updateScreen();
    if(isTimer)
    {
        int delta = timeGame*1000-elapsedTime();
        if(delta<=0)
            endGameTimer();
        else
            de->updateGameDataTimer(delta/1000);
    }

    checkOutsideScene(listProjectile);
    checkOutsideScene(listAsteroide);
    checkOutsideScene(listSmallAsteroide);
    checkOutsideScene(listBonus);
    checkOutsideScene(listAlienSpaceship);

    for(int i = 0;i<listSpaceship.size();i++)
    {
        checkCollisionSpaceshipAndList(i,listProjectile);
        checkCollisionSpaceshipAndList(i,listAsteroide);
        checkCollisionSpaceshipAndList(i,listSmallAsteroide);
    }
    de->updateGameData();
    //Explode all the supernova
    for(int i = 0;i<listSupernova.size();i++)
    {
        delete listSupernova[i];
        listSupernova[i]=0;
    }
    listSupernova.clear();

    runTestCollision(listProjectile);
    clearList(listProjectile);

    runTestCollision(listAsteroide);
    runTestCollision(listSmallAsteroide);
}

int GameEngine::elapsedTime()
{
    if(elapsedTimer.isValid())
        return timeAlreadyCounted + elapsedTimer.elapsed();
    else
        return timeAlreadyCounted;
}

void GameEngine::endGameTimer()
{
    timerControle();
    if(!hasSomeoneWon)
    {
        hasSomeoneWon = true;

        emit endGame();
        QString playerName;

        if(ship1()->getScore()>ship2()->getScore())
            playerName = QString(ship1()->getPlayerName());
        else if(ship1()->getScore()<ship2()->getScore())
            playerName = QString(ship2()->getPlayerName());

        if(ship1()->getScore()!=ship2()->getScore())
            QMessageBox::information(de,
                                     tr("End of the game"),
                                     QString(tr("%1 has won !")).arg(playerName),
                                     QMessageBox::Ok);
        else
            QMessageBox::information(de,
                                     tr("End of the game"),
                                     QString(tr("No one has won ... Egality !")),
                                     QMessageBox::Ok);
    }
}

void GameEngine::endGameDeathMatch(Spaceship* _ship)
{
    // get point player
    //gameEngine->spaceship;
    if(_ship==0)
    {
        QMessageBox::information(de,
                                 tr("End of the game"),
                                 tr("End of the game"),
                                 QMessageBox::Ok);
    }
    else
    {
        if(!hasSomeoneWon)
        {
            hasSomeoneWon = true;
            de->updateGameData();
            QString playerName;
            if(_ship==ship1())
                playerName = QString(ship2()->getPlayerName());
            else if(_ship==ship2())
                playerName = QString(ship1()->getPlayerName());
            QMessageBox::information(de,
                                     tr("End of the game"),
                                     QString(tr("%1 has won !")).arg(playerName),
                                     QMessageBox::Ok);
        }
    }
}

void GameEngine::escapeGame()
{
    timerControle();

    QMessageBox messageExit;

    messageExit.setWindowTitle(tr("End of the game"));
    messageExit.setText(tr("Do you want to stop the current game ?"));
    messageExit.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageExit.setDefaultButton(QMessageBox::No);

    messageExit.setButtonText(QMessageBox::Yes,tr("Yes"));
    messageExit.setButtonText(QMessageBox::No,tr("No"));

    if(messageExit.exec() == QMessageBox::Yes)
        emit endGame();
    timerControle();
}

void GameEngine::elemenDestroyed(Destroyable* _destroyItem, int nbPoint, Shooter forShip)
{
    if(Spaceship* s = dynamic_cast<Spaceship*>(_destroyItem))
    {
        timerControle();
        endGameDeathMatch(s);
        emit endGame();
    }
    else
    {
        if(forShip==Player1)
            ship1()->addPoint(nbPoint);
        else if(forShip==Player2)
            ship2()->addPoint(nbPoint);

        if(Asteroid* a = dynamic_cast<Asteroid*>(_destroyItem))
        {
            if(a->isSmall())
                removeSmallAsteroid(a);
            else
                removeAsteroid(a);
        }
        else if(AlienSpaceship* a = dynamic_cast<AlienSpaceship*>(_destroyItem))
        {
            removeAlienSpaceship(a);
            if(forShip==Player1)
                ship1()->addBonus(se->generateBonus());
            else if(forShip==Player2)
                ship2()->addBonus(se->generateBonus());
        }
		else if(Blackship* s = dynamic_cast<Blackship*>(_destroyItem))
			removeBlackship(s);
    }
}

void GameEngine::detectObjectAfterMiddleZone(const QList<Displayable*>& list, QList<Projectile*>& projList, Shooter playerActivated)
{
    for(auto it = list.begin(); it != list.end(); ++it)
        if((*it)->pos().x() < de->sceneSize().width()/2.0 && playerActivated == Player1
                || (*it)->pos().x() > de->sceneSize().width()/2.0 && playerActivated == Player2)
            projList.append(static_cast<Projectile*>(*it));
}

void GameEngine::enableAntiGravity(Shooter playerActivated)
{
    QList<Projectile*> projectilesToAntigravitate;

    detectObjectAfterMiddleZone(listProjectile, projectilesToAntigravitate, playerActivated);
    detectObjectAfterMiddleZone(listAsteroide, projectilesToAntigravitate, playerActivated);
    detectObjectAfterMiddleZone(listSmallAsteroide, projectilesToAntigravitate, playerActivated);

    for(auto it = projectilesToAntigravitate.begin(); it != projectilesToAntigravitate.end(); ++it)
        (*it)->enableAntiGravity(playerActivated);
}

void GameEngine::freezePlayer(int duration, Shooter playerDest)
{
    Spaceship* ss;
    if(playerDest == Player1)
        ss = ship1();
    else
        ss = ship2();

    if(!ss->getIsFrozen())
    {
        ss->freeze();
        QTimer::singleShot(duration,ss,SLOT(unfreeze()));
    }
}

void GameEngine::rotationProcess(int wiimote, qreal angle)
{
    if(wiimote == 0)
        ship1()->rotate(angle);
    else
        ship2()->rotate(angle);
}

void GameEngine::positionProcess()
{
	QPair<QPoint, QPoint> positions = kinect->getHandsPosition();
	ship1()->setY(positions.second.y());
    ship2()->setY(positions.first.y());
}

void GameEngine::timerControle(int tps)
{
    if(isRunning)
    {
        killTimer(idTimer);
        idTimer = -1;

        timeAlreadyCounted += elapsedTimer.elapsed();
        elapsedTimer.invalidate();

        emit signalPause(true);
    }

    else
    {
        idTimer = startTimer(tps);

        elapsedTimer.start();

        emit signalPause(false);
    }
    isRunning = !isRunning;
}

void GameEngine::addProjectile(Projectile * _inProjectile)
{
    de->addItemScene(_inProjectile);
	listProjectile.append(_inProjectile);
}

void GameEngine::addShip(Spaceship *_inSpaceship)
{

    de->addItemScene(_inSpaceship);
    listSpaceship.append(_inSpaceship);
    connect(_inSpaceship,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void GameEngine::removeShip(Spaceship *_inSpaceship)
{
    int l_index = listSpaceship.indexOf(_inSpaceship);
    if(l_index!=-1)
    {
        delete listSpaceship[l_index];
        listSpaceship[l_index]=0;
    }
}

void GameEngine::addBonus(Bonus *_inBonus)
{
    de->addItemScene(_inBonus);
    soe->playSound(SatelliteSound);
    listBonus.append(_inBonus);
}

void GameEngine::addAsteroid(Asteroid *_inAsteroid)
{
    de->addItemScene(_inAsteroid);
    listAsteroide.append(_inAsteroid);
    connect(_inAsteroid,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void GameEngine::addSmallAsteroid(Asteroid *_inAsteroid)
{
    de->addItemScene(_inAsteroid);
    listSmallAsteroide.append(_inAsteroid);
    connect(_inAsteroid,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void GameEngine::addAlienSpaceship(AlienSpaceship *_inAlienSpaceship)
{
    de->addItemScene(_inAlienSpaceship);
    listAlienSpaceship.append(_inAlienSpaceship);
    connect(_inAlienSpaceship,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void GameEngine::addBlackship(Blackship *_blackship)
{
    de->addItemScene(_blackship);
    listBlackship.append(_blackship);
    connect(_blackship,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void GameEngine::removeBlackship(Blackship *_blackship)
{
    int l_index = listBlackship.indexOf(_blackship);
    if(l_index!=-1)
    {
        delete listBlackship[l_index];
        listBlackship[l_index]=0;
    }
}

void GameEngine::addSupernova(Supernova *_inSupernova)
{
    listSupernova.append(_inSupernova);
}

void GameEngine::removeAlienSpaceship(AlienSpaceship *_inAlienSpaceship)
{
    int l_index = listAlienSpaceship.indexOf(_inAlienSpaceship);
    if(l_index!=-1)
    {
        delete listAlienSpaceship[l_index];
        listAlienSpaceship[l_index]=0;
    }
}

void GameEngine::removeAsteroid(Asteroid *_inAsteroide)
{
    int l_index = listAsteroide.indexOf(_inAsteroide);
    if(l_index!=-1)
    {
        delete listAsteroide[l_index];
        listAsteroide[l_index]=0;
    }
}

void GameEngine::removeSmallAsteroid(Asteroid *_inAsteroide)
{
    int l_index = listSmallAsteroide.indexOf(_inAsteroide);
    if(l_index!=-1)
    {
        delete listSmallAsteroide[l_index];
        listSmallAsteroide[l_index]=0;
    }
}

void GameEngine::clearList(QList<Displayable*> &list)
{
    for(int i = 0;i<list.size();++i)
      if(list[i]==0)
          list.removeAt(i--);
}

void GameEngine::checkOutsideScene(QList<Displayable*> &list)
{
    if(list.empty())
        return;

    for(int i = 0;i<list.size();i++)
        if(list[i] != 0)
        {
            int l_w = 0;
            int l_h = 0;

            QMutexLocker l(mutex);
            if(list[i]->isPixmap())
            {
                l_w = list[i]->sizePixmap().width();
                l_h = list[i]->sizePixmap().height();
            }

            if(list[i]->pos().x()-l_w > sceneSize().width() || list[i]->pos().x()+l_w < 0
            || list[i]->pos().y() > sceneSize().height() || list[i]->pos().y()+l_h < 0)
                {
                    delete list[i];
                    list[i] = 0;
                }
        }

    clearList(list);
}

void GameEngine::removeItemScene(Displayable* item)
{
    de->removeItemScene(item);
}

bool GameEngine::checkCollisionItemAndList(const int i_list1,QList<Displayable*> &list1,QList<Displayable*> &list2)
{
    if(list2.empty() || list1.empty() || list2[0] == 0 || list1[i_list1] == 0)
        return false;

    QMutexLocker l(mutex);
    if(list2[0]->getTypeObject() == tAlien && list1[i_list1]->getTypeObject() == tProj)
        if(dynamic_cast<Projectile*>(list1[i_list1])->getFrom()==Alien)
            return false;

	if((list2[0]->getTypeObject() == tAlien || list2[0]->getTypeObject() == tBlackShip) && (list1[i_list1]->getTypeObject() == tAsteroid || list1[i_list1]->getTypeObject() == tSmallAsteroid))
		return false;

    for(int j = 0;j<list2.size();j++)
    {
        if(list2[j]==0)
            continue;
        if(list1[i_list1] != list2[j] && list1[i_list1]->collidesWithItem(list2[j],Qt::IntersectsItemShape))
        {
            if(list1[i_list1]->getTypeObject() == tProj)
            {
                if(Destroyable* d = dynamic_cast<Destroyable*>(list2[j]))
                {
                    if(d->gonnaDead(list1[i_list1]->getPower()))
                        if(list2[j]->getTypeObject()==tAsteroid)
                            dynamic_cast<Asteroid*>(list2[j])->collision(list1[i_list1]->getAngle());

                    d->receiveAttack(list1[i_list1]->getPower(),list2[j]->getNbPoint(),dynamic_cast<Projectile*>(list1[i_list1])->getFrom());

                    delete list1[i_list1];
                    list1[i_list1] = 0;

                    return false;
                }
                else if(list2[j]->getTypeObject() == tBonus)
                {
                    Projectile* p = dynamic_cast<Projectile*>(list1[i_list1]);
                    Bonus* b = dynamic_cast<Bonus*>(list2[j]);

                    if(gameMode==Timer)
                    {
                        if(p->getFrom()==Player1)
                            ship1()->addPoint(b->getNbPoint());
                        else if(p->getFrom()==Player2)
                            ship2()->addPoint(b->getNbPoint());
                    }
                    //We don't delete the pointer here, it'll be deleted in the class spaceship
                    //We only remove the item from the list
                    list2[j] = 0;
                    removeItemScene(b);

                    if(p->getFrom() == Player1)
                        ship1()->addBonus(b);
                    else if(p->getFrom() == Player2)
                        ship2()->addBonus(b);

                    delete list1[i_list1];
                    list1[i_list1]=0;

                    return true;
                }
            }
            else if(list1[i_list1]->getTypeObject() == tSmallAsteroid && list2[j]->getTypeObject() == tSmallAsteroid)
            {
                if(dynamic_cast<Asteroid*>(list1[i_list1])->getIdParent() == dynamic_cast<Asteroid*>(list2[j])->getIdParent() && dynamic_cast<Asteroid*>(list2[j])->getIdParent() != 0)
                    return false;
                else
                {
                    delete list1[i_list1];
                    list1[i_list1] = 0;

                    delete list2[j];
                    list2[j] = 0;

                    return true;
                }
            }
            else if(list1[i_list1]->getTypeObject() == tAsteroid && list2[j]->getTypeObject() == tAsteroid)
            {
                dynamic_cast<Asteroid*>(list1[i_list1])->collision(list2[j]->getAngle());
                dynamic_cast<Asteroid*>(list2[j])->collision(list1[i_list1]->getAngle());
            }
            else if(list1[i_list1]->getTypeObject() == tAsteroid && list2[j]->getTypeObject() == tSpaceship)
                dynamic_cast<Asteroid*>(list1[i_list1])->collision(list2[j]->getAngle());

            delete list1[i_list1];
            list1[i_list1] = 0;

            delete list2[j];
            list2[j] = 0;

            return true;
        }
    }

    return false;
}

bool GameEngine::checkCollisionSpaceshipAndList(const int i,QList<Displayable*> &list)
{
    if(list.empty() || listSpaceship.empty())
        return false;

    for(int j = 0;j<list.size();j++)
    {
        QMutexLocker l(mutex);
        if(list[j]==0)
            return false;

        if(listSpaceship[i]->collidesWithItem(list[j],Qt::IntersectsItemShape))
        {
            if(gameMode==DeathMatch)
                listSpaceship[i]->receiveAttack(list[j]->getPower());
            else if(gameMode==Timer && list[j]->getTypeObject() ==tProj)
                if(dynamic_cast<Projectile*>(list[j])->getFrom()==Player1)
                    ship1()->addPoint(list[j]->getNbPoint());
                else if(dynamic_cast<Projectile*>(list[j])->getFrom()==Player2)
                    ship2()->addPoint(list[j]->getNbPoint());

            if(list[j]->getTypeObject()==tAsteroid)
                dynamic_cast<Asteroid*>(list[j])->collision((listSpaceship[i]->getAngle()));

            delete list[j];
            list[j] = 0;
            clearList(list);

            return true;
        }
    }
    return false;
}

void GameEngine::runTestCollision(QList<Displayable*> &list)
{
    if(list.empty())
        return;
        for(int i = 0;i<list.size();i++)
            if(checkCollisionItemAndList(i,list,listAsteroide)
            || checkCollisionItemAndList(i,list,listSmallAsteroide)
            || checkCollisionItemAndList(i,list,listBlackship)
            || checkCollisionItemAndList(i,list,listAlienSpaceship)
			|| checkCollisionItemAndList(i,list,listBonus))
                continue;

        clearList(listAsteroide);
        clearList(listSmallAsteroide);
        clearList(listBonus);
        clearList(listAlienSpaceship);
		clearList(listBlackship);
}
