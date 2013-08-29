#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include "include/engine/WiimoteEngine.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectDialog(WiimoteEngine* wiimoteEngine, QWidget *parent = 0);
    ~ConnectDialog();
    
private:
    Ui::ConnectDialog *ui;
    WiimoteEngine* wiimoteEngine;

private slots:
    void connectWiimotes();
    void connectKinect();
    void performCalibration();
    void checkAndClose();
};

#endif // CONNECTDIALOG_H
