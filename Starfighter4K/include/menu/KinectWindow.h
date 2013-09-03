#ifndef KINECTWINDOW_H
#define KINECTWINDOW_H

#include "include/config/Define.h"

namespace Ui {
class KinectWindow;
}

class QTime;
class WiimoteEngine;
class GameEngine;
class QKinect;
class Overlay;

class KinectWindow : public QMainWindow
{
    Q_OBJECT
    
public:
	explicit KinectWindow(WiimoteEngine* we, QKinect* kinect, QWidget *parent = 0);
    ~KinectWindow();

public slots:
    void endGame();
    
private slots:
	void handsMoved();
	void back();
    void on_btnGame_clicked();
	void on_btnOptions_clicked();
	void on_btnValidateOptions_clicked();
    void on_btnDeathmatch_clicked();
    void on_btnTimer_clicked();
    void on_btnValidateTime_clicked();
    void on_btnPlus_clicked();
    void on_btnMinus_clicked();
    void on_btnShip1P1_clicked();
    void on_btnShip2P1_clicked();
    void on_btnShip3P1_clicked();
    void on_btnShip1P2_clicked();
    void on_btnShip2P2_clicked();
    void on_btnShip3P2_clicked();
    void on_btnFreezeP1_clicked();
    void on_btnAntigravityP1_clicked();
    void on_btnGuidedP1_clicked();
    void on_btnTrackingP1_clicked();
    void on_btnRootP1_clicked();
    void on_btnFreezeP2_clicked();
    void on_btnAntigravityP2_clicked();
    void on_btnGuidedP2_clicked();
    void on_btnTrackingP2_clicked();
    void on_btnRootP2_clicked();

private:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
    Ui::KinectWindow *ui;
    QTime timer;
    void keyPressEvent(QKeyEvent *);
    SpaceshipType p1Ship;
    SpaceshipType p2Ship;
    TypeSpecialBonus p1Bonus;
    TypeSpecialBonus p2Bonus;
    GameMode gameMode;
    void updateTimerDisplay();
    void validateShips();
    void validateBonus();
    WiimoteEngine* we;
	QKinect* kinect;
    GameEngine* ge;
	QMediaPlayer *menuMusic;
	Overlay* overlay;
	QPoint hand1;
	QPoint hand2;
	QPixmap background;
};

#endif // KINECTWINDOW_H
