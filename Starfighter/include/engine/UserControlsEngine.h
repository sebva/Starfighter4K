#ifndef USER_CONTROLS_ENGINE_H
#define USER_CONTROLS_ENGINE_H

#include "include/enum/Enum.h"

class GameEngine;
class DisplayEngine;
class QTimer;

class UserControlsEngine : public QObject
{
    Q_OBJECT

public:
    UserControlsEngine(GameEngine *ge);
    ~UserControlsEngine();

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void timerEvent(QTimerEvent *event);

    void clearActionList();

public slots:
    void callSupernovae();
    void pauseGame(bool etat);
    void endGame();

private:
    QMap<int,Action>        actions;
    QMap<Action,Qt::Key>    myKey;
    GameEngine *            gameEngine;
    DisplayEngine *         display;
    QList<Action>           actionList;
    QTimer *                novaeCall;
    int                     idTimer;

    QElapsedTimer           countTimer;

    bool hasEnd;
    bool hasBegin;
    int pauseTime;


};
#endif
