#ifndef MAINDIALOG_H
#define MAINDIALOG_H

class GameEngine;
class NewGameDialog;
class WiimoteEngine;

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    void setGameEngine(GameEngine *);
    WiimoteEngine* getWiimoteEngine() const {return we;}
public slots:
    void endGame();
    void stopMusic();
    
private slots:
    void on_btnPlay_clicked();

    void on_btnOptions_clicked();

    void on_btnAbout_clicked();

private:
    Ui::MainDialog *ui;
    GameEngine *ge;
    NewGameDialog *ngd;
    WiimoteEngine* we;

    QMediaPlayer *menuMusic;
};

#endif // MAINDIALOG_H
