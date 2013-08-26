#include "include/engine/UserControlsEngine.h"
#include "include/engine/GameEngine.h"
#include "include/engine/DisplayEngine.h"
#include "include/engine/WiimoteEngine.h"
#include "include/game/Spaceship.h"
#include "include/game/Supernova.h"

#include "include/utils/Settings.h"
#include "include/config/Define.h"

#include <lib/wiiuse/wiiuse.h>
#include "include/stable.h"

#define PLAYER_1 0
#define PLAYER_2 1

UserControlsEngine::UserControlsEngine(GameEngine *ge, WiimoteEngine *we): gameEngine(ge), wiimoteEngine(we), hasEnd(false), hasBegin(true), isPaused(false), pauseTime(NOVATIMER)
{
    display = gameEngine->displayEngine();

    actions.insert(WIIMOTE_BUTTON_A, Shoot);
    actions.insert(WIIMOTE_BUTTON_B, Shoot);
    actions.insert(WIIMOTE_BUTTON_UP, Top);
    actions.insert(WIIMOTE_BUTTON_DOWN, Bottom);
    actions.insert(WIIMOTE_BUTTON_MINUS, NormalBonus);
    actions.insert(WIIMOTE_BUTTON_PLUS, aSpecialBonus);
    actions.insert(WIIMOTE_BUTTON_HOME, Pause);

    novaeCall = new QTimer(this);
    novaeCall->setSingleShot(true);
    novaeCall->start(NOVATIMER);
    countTimer.start();
    idTimer = startTimer(REFRESH);

    connect(novaeCall,SIGNAL(timeout()),this,SLOT(callSupernovae()));
    connect(gameEngine,SIGNAL(signalPause(bool)),this,SLOT(pauseGame(bool)));
    connect(gameEngine,SIGNAL(endGame()),this,SLOT(endGame()));
    connect(wiimoteEngine, SIGNAL(button_pressed(int,int)), this, SLOT(wiimotePressProcess(int,int)));
    connect(wiimoteEngine, SIGNAL(button_released(int,int)), this, SLOT(wiimoteReleaseProcess(int,int)));
}

UserControlsEngine::~UserControlsEngine()
{
    delete novaeCall;
    //MainDialog deletes WiimoteEngine
    //GameEngine deletes DisplayEngine and UserControlsEngine
}

void UserControlsEngine::wiimotePressProcess(int button, int wiimote)
{
    if(!isPaused && actions.count(button) >= 1)
    {
        Action action = actions[button];
        actionList.append(QPair<Action, int>(action, wiimote));

        Spaceship* ss = (wiimote == PLAYER_1) ? gameEngine->ship1() : gameEngine->ship2();

        if(action == Shoot || action == NormalBonus || action == aSpecialBonus)
        {
            novaeCall->start(NOVATIMER);
            countTimer.restart();
        }

        if(action == Shoot)
            ss->attack();
        else if(action == NormalBonus)
            ss->triggerBonus();
        else if(action == aSpecialBonus)
            ss->triggerSpecialAttack();
        else if(action == Pause)
            gameEngine->escapeGame();
    }
}

void UserControlsEngine::wiimoteReleaseProcess(int button, int wiimote)
{
    if(actions.count(button) >= 1)
    {
        QPair<Action, int> pair(actions[button], wiimote);

        actionList.removeAll(pair);
    }
}

void UserControlsEngine::keyPressEvent(QKeyEvent * event)
{
    Action action;
    Shooter player;

    switch(event->key())
    {
        case Qt::Key_W:
            actionList.append(QPair<Action,int>(Top,PLAYER_1));
            break;

        case Qt::Key_S:
            actionList.append(QPair<Action,int>(Bottom,PLAYER_1));
            break;

        case Qt::Key_D:
            player = Player1;
            action = Shoot;
            actionList.append(QPair<Action,int>(Shoot,PLAYER_1));
            break;

        case Qt::Key_Q:
            gameEngine->ship1()->triggerBonus();
        break;

        case Qt::Key_A:
            gameEngine->ship1()->triggerSpecialAttack();
        break;

        case Qt::Key_I:
            actionList.append(QPair<Action,int>(Top,PLAYER_2));
            break;

        case Qt::Key_K:
            actionList.append(QPair<Action,int>(Bottom,PLAYER_2));
            break;

        case Qt::Key_J:
            player = Player2;
            action = Shoot;
            actionList.append(QPair<Action,int>(Shoot,PLAYER_2));
            break;

        case Qt::Key_O:
            gameEngine->ship2()->triggerBonus();
        break;

        case Qt::Key_L:
            gameEngine->ship2()->triggerSpecialAttack();
        break;
    }

    if((!event->isAutoRepeat() && (action == Shoot && player == Player1)))
    {
        gameEngine->ship1()->attack();
        novaeCall->start(NOVATIMER);
        countTimer.restart();
    }

    if((!event->isAutoRepeat() && (action == Shoot && player == Player2)))
    {
        gameEngine->ship2()->attack();
        novaeCall->start(NOVATIMER);
        countTimer.restart();
    }

}

void UserControlsEngine::keyReleaseEvent(QKeyEvent * event)
{

    switch(event->key())
    {
        case Qt::Key_W:
            actionList.removeAll(QPair<Action,int>(Top,PLAYER_1));
            break;

        case Qt::Key_S:
            actionList.removeAll(QPair<Action,int>(Bottom,PLAYER_1));
            break;

        case Qt::Key_D:
            actionList.removeAll(QPair<Action,int>(Shoot,PLAYER_1));
            break;

        case Qt::Key_I:
            actionList.removeAll(QPair<Action,int>(Top,PLAYER_2));
            break;

        case Qt::Key_K:
            actionList.removeAll(QPair<Action,int>(Bottom,PLAYER_2));
            break;

        case Qt::Key_J:
            actionList.removeAll(QPair<Action,int>(Shoot,PLAYER_2));
            break;
    }
}

void UserControlsEngine::timerEvent(QTimerEvent *event)
{
    hasBegin = false;

    for(auto values = actionList.begin(); values != actionList.end(); values++)
    {
        Spaceship* ss = (values->second == PLAYER_1)?gameEngine->ship1():gameEngine->ship2();
        switch(values->first)
        {
            case Top:
                ss->top();
            break;

            case Bottom:
                ss->bottom();
            break;

            default:
                break;
        }
    }
}

void UserControlsEngine::pauseGame(bool etat)
{
    if(!hasBegin)
    {
        isPaused = etat;
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
    isPaused = true;
    hasEnd = true;
    clearActionList();
    killTimer(idTimer);
}
