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
class QGraphicsTextItem;

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
    HUDWidget* getHud() { return hud; }

	void startCountDown();

	void showMessage(const QString&);
	void removeMessage();

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

public slots:
    void updateScreen();
    void moveBG();

private slots:
    void removeExplosionScreen();
	void changeCountDown();

private:
    void creatHUD();
    void switchFullScreen();

    void setProgressHP1(int _value);
    void setProgressHP2(int _value);
    void setProgressShield1(int _value);
    void setProgressShield2(int _value);
    void setGameScore1(int _value);
    void setGameScore2(int _value);

    const static int offset = 10;
    GameEngine *gameEngine;
    QPixmap *explosionPicture;
    QSplashScreen *splash;
    QGraphicsPixmapItem* bgScene;
    QPixmap bg;
    QGraphicsScene * scene;
    QGraphicsView * view;
    qreal angleBg;

    QTime* affiche;
	QGraphicsTextItem* text;
	QGraphicsTextItem* message;
	QTimer* tCountDown;
	int countDown;
    HUDWidget* hud;

    bool isFullScreen;
};
#endif
