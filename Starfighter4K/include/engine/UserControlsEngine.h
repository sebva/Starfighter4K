#ifndef USER_CONTROLS_ENGINE_H
#define USER_CONTROLS_ENGINE_H

#include "include/enum/Enum.h"

class GameEngine;
class DisplayEngine;
class QTimer;
class WiimoteEngine;

class UserControlsEngine : public QObject
{
    Q_OBJECT

public:
    UserControlsEngine(GameEngine *ge, WiimoteEngine *we);
    ~UserControlsEngine();

    void timerEvent(QTimerEvent *event);
    void clearActionList();

public slots:
    void callSupernovae();
    void pauseGame(bool etat);
    void endGame();
    void wiimotePressProcess(int button, int wiimote);
    void wiimoteReleaseProcess(int button, int wiimote);

private:
    QMap<int,Action>        actions;

    GameEngine *            gameEngine;
    DisplayEngine *         display;
    WiimoteEngine *         wiimoteEngine;
    QList<QPair<Action, int>> actionList;
    QTimer *                novaeCall;
    int                     idTimer;

    QElapsedTimer           countTimer;

    bool hasEnd;
    bool hasBegin;
    bool isPaused;
    int pauseTime;


};
#endif
