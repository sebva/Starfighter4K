#ifndef DISPLAY_ENGINE_H
#define DISPLAY_ENGINE_H

#include "include/enum/Enum.h"

class QLCDNumber;
class QTime;
class QGridLayout;
class QGraphicsScene;
class QGraphicsView;
class QWidget;
class QMainWindow;
class QLabel;
class QProgressBar;
class GameEngine;
class Displayable;
class QPixmap;
class QSplashScreen;
class HUDWidget;

class DisplayEngine : public QMainWindow
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

    GameEngine *gameEngine;
    QPixmap *explosionPicture;
    QSplashScreen *splash;

    QGraphicsScene * scene;
    QGraphicsView * view;

    QTime* affiche;

    HUDWidget* hud;

    bool isFullScreen;
};
#endif
