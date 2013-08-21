#ifndef DISPLAY_ENGINE_H
#define DISPLAY_ENGINE_H

#include "include/enum/Enum.h"

class QLCDNumber;
class QTime;
class QGridLayout;
class QGraphicsScene;
class QGraphicsView;
class QWidget;
class QLabel;
class QProgressBar;
class GameEngine;
class Displayable;
class QPixmap;
class QSplashScreen;

class DisplayEngine : public QWidget
{
    Q_OBJECT
public:
    DisplayEngine(GameEngine *ge,QWidget *parent);
    ~DisplayEngine();

    QRect sceneSize() const;
    qreal xminWarzone() const;
    qreal xmaxWarZone() const;

    void addItemScene(Displayable* item);
    void removeItemScene(Displayable* item);

    void updateGameData();
    void updateGameDataTimer(int s);

    void explosionScreen();

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

public slots:
    void updateScreen();

private slots:
    void removeExplosionScreen();

private:
    void creatHUD();
    void switchFullScreen();

    void setProgressHP1(int _value);
    void setProgressHP2(int _value);
    void setProgressShield1(int _value);
    void setProgressShield2(int _value);
    void setGameScore1(int _value);
    void setGameScore2(int _value);

    void setBonusProject1(TypeProjectiles _value = ProjSimple);
    void setBonusProject2(TypeProjectiles _value = ProjSimple);

    void setBonusSpeed1(int _value = 0);
    void setBonusSpeed2(int _value = 0);

    GameEngine *gameEngine;
    QPixmap *explosionPicture;
    QSplashScreen *splash;

    QGraphicsScene * scene;
    QGraphicsView * view;

    QWidget * downHUD;

    QGridLayout * bonusPlayerOne;
    QGridLayout * bonusPlayerTwo;

    bool isFullScreen;
    bool isTimer;

    QPixmap pixSpeed;
    QPixmap pixProj;
    QPixmap pixHP;

    // widget used for the HUD
    QTime      * affiche;
    QLCDNumber * timer;
    QLCDNumber * scoreP1;
    QLCDNumber * scoreP2;

    QLabel * lBSpeed1;
    QLabel * lBHP1;
    QLabel * lBProjectile1;

    QLabel * lBSpeed2;
    QLabel * lBHP2;
    QLabel * lBProjectile2;

    QLabel * imSpeed1;
    QLabel * imHP1;
    QLabel * imProj1;

    QLabel * imSpeed2;
    QLabel * imHP2;
    QLabel * imProj2;

    QProgressBar * HP1;
    QProgressBar * HP2;
    QProgressBar * shield1;
    QProgressBar * shield2;
};
#endif
