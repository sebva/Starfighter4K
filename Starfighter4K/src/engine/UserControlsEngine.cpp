#include "include/engine/UserControlsEngine.h"
#include "include/engine/GameEngine.h"
#include "include/engine/DisplayEngine.h"

#include "include/game/Spaceship.h"
#include "include/game/Supernova.h"

#include "include/utils/Settings.h"
#include "include/config/Define.h"

UserControlsEngine::UserControlsEngine(GameEngine *ge): gameEngine(ge), hasEnd(false), hasBegin(true),pauseTime(NOVATIMER)
{
    myKey = Settings::getGlobalSettings().playersControls();

    display = gameEngine->displayEngine();

    actions.insert(myKey[aTop1],aTop1);
    actions.insert(myKey[aBottom1],aBottom1);
    actions.insert(myKey[aShoot1],aShoot1);

    actions.insert(myKey[aTop2],aTop2);
    actions.insert(myKey[aBottom2],aBottom2);
    actions.insert(myKey[aShoot2],aShoot2);

    novaeCall = new QTimer(this);
    novaeCall->setSingleShot(true);
    novaeCall->start(NOVATIMER);
    countTimer.start();
    idTimer = startTimer(REFRESH);

    connect(novaeCall,SIGNAL(timeout()),this,SLOT(callSupernovae()));
    connect(gameEngine,SIGNAL(signalPause(bool)),this,SLOT(pauseGame(bool)));
    connect(gameEngine,SIGNAL(endGame()),this,SLOT(endGame()));

}

UserControlsEngine::~UserControlsEngine()
{
    delete novaeCall;

    //GameEngine delete DisplayEngine and UserControlsEngine
}

void UserControlsEngine::keyPressEvent(QKeyEvent * event)
{

    Action action = actions[event->key()];

    switch(action)
    {
        case(aTop1):
        actionList.append(aTop1);
        break;

        case(aBottom1):
        actionList.append(aBottom1);
        break;

        case(aShoot1):
        break;

        case(aTop2):
        actionList.append(aTop2);
        break;

        case(aBottom2):
        actionList.append(aBottom2);
        break;

        case(aShoot2):
        break;
    }


    if((!event->isAutoRepeat() && (action == aShoot1)))
    {
        gameEngine->ship1()->attack();
        novaeCall->start(NOVATIMER);
        countTimer.restart();
    }

    if((!event->isAutoRepeat() && (action == aShoot2)))
    {
        gameEngine->ship2()->attack();
        novaeCall->start(NOVATIMER);
        countTimer.restart();
    }

}

void UserControlsEngine::keyReleaseEvent(QKeyEvent * event)
{

    Action action = actions[event->key()];

    switch(action)
    {
        case(aTop1):
        actionList.removeAll(aTop1);
        break;

        case(aBottom1):
        actionList.removeAll(aBottom1);
        break;

        case(aShoot1):
        break;

        case(aTop2):
        actionList.removeAll(aTop2);
        break;

        case(aBottom2):
        actionList.removeAll(aBottom2);
        break;

        case(aShoot2):
        break;
    }
}

void UserControlsEngine::timerEvent(QTimerEvent *event)
{
    hasBegin = false;

    QList<Action>::iterator values;

    for(values = actionList.begin(); values != actionList.end(); values++)
    {
        switch(*values)
        {
            case(aTop1):
            gameEngine->ship1()->top();
            break;

            case(aBottom1):
            gameEngine->ship1()->bottom();
            break;

            case(aShoot1):
            break;

            case(aTop2):
            gameEngine->ship2()->top();
            break;

            case(aBottom2):
            gameEngine->ship2()->bottom();
            break;

            case(aShoot2):
            break;
        }
    }
}

void UserControlsEngine::pauseGame(bool etat)
{
    if(!hasBegin)
    {
        if(etat)
        {
            novaeCall->stop();
            pauseTime = countTimer.elapsed();
        }
        else
        {
            pauseTime = NOVATIMER-pauseTime;
            novaeCall->start(pauseTime);
            countTimer.restart();
        }
    }
}

void UserControlsEngine::clearActionList()
{
    actionList.clear();
}

void UserControlsEngine::callSupernovae()
{
    Supernova *supernova = new Supernova(display->sceneSize().width() / 2, display->sceneSize().height() / 2, gameEngine);
    gameEngine->addSupernova(supernova);
    novaeCall->start(NOVATIMER);
    countTimer.restart();
}

void UserControlsEngine::endGame()
{
    hasEnd = true;
    clearActionList();
    killTimer(idTimer);
}
