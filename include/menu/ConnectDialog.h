#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include "include/engine/WiimoteEngine.h"

class QKinect;
class QSplashScreen;

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectDialog(WiimoteEngine* wiimoteEngine, QKinect* kinect, QWidget *parent = 0);
    ~ConnectDialog();
    
private:
    Ui::ConnectDialog *ui;
    WiimoteEngine* wiimoteEngine;
    QKinect* kinect;
	QSplashScreen* greenScreen;

private slots:
    void connectWiimotes();
    void connectKinect();
    void performCalibration();
    void checkAndClose();
};

#endif // CONNECTDIALOG_H
