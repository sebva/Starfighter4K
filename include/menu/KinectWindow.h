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
class BlurPushButton;

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

protected:
	void paintEvent(QPaintEvent *event);

private:
	void unselectShips();
	void unselectBonuses();
    Ui::KinectWindow *ui;
    QTime timer;
    void keyPressEvent(QKeyEvent *);
    SpaceshipType p1Ship;
    SpaceshipType p2Ship;
    TypeSpecialBonus p1Bonus;
    TypeSpecialBonus p2Bonus;
    GameMode gameMode;
    void updateTimerDisplay();
    WiimoteEngine* we;
	QKinect* kinect;
    GameEngine* ge;
	QMediaPlayer *menuMusic;
	QPoint hand1;
	QPoint hand2;
	QPixmap background;
	BlurPushButton** hoverButtons;
	QButtonGroup p1ShipsGroup;
	QButtonGroup p2ShipsGroup;
	QButtonGroup p1BonusGroup;
	QButtonGroup p2BonusGroup;
	bool kinectActive;

private slots:
    void validateShips(int);
    void validateBonus(int);
};

#endif // KINECTWINDOW_H
