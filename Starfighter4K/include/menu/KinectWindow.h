#ifndef KINECTWINDOW_H
#define KINECTWINDOW_H

#include <QMainWindow>

namespace Ui {
class KinectWindow;
}

class QTime;

class KinectWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit KinectWindow(QWidget *parent = 0);
    ~KinectWindow();
    
private slots:
    void on_btnGame_clicked();

    void on_btnDeathmatch_clicked();

    void on_btnTimer_clicked();

    void on_btnValidateTime_clicked();

    void on_btnPlus_clicked();

    void on_btnMinus_clicked();

private:
    Ui::KinectWindow *ui;
    QTime timer;
    void keyPressEvent(QKeyEvent *);

    void updateTimerDisplay();
};

#endif // KINECTWINDOW_H
