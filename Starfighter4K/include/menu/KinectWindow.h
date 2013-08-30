#ifndef KINECTWINDOW_H
#define KINECTWINDOW_H

#include "include/config/Define.h"

namespace Ui {
class KinectWindow;
}

class QTime;
class WiimoteEngine;
class GameEngine;

class KinectWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit KinectWindow(WiimoteEngine* we, QWidget *parent = 0);
    ~KinectWindow();

public slots:
    void endGame();
    
private slots:
    void on_btnGame_clicked();

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
    GameEngine* ge;
};

#endif // KINECTWINDOW_H
