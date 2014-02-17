#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>

namespace Ui {
class StateWidget;
}

enum SystemState {
	SystemStateUninitialized = 1,
    SystemStateFailed = 2,
	SystemStateReady = 3
};

class StateWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StateWidget(QWidget *parent = 0);
    ~StateWidget();
    SystemState getStatus();
    void setStatus(SystemState status);
    void setSystemName(QString name);
    
private:
    Ui::StateWidget *ui;
    void mousePressEvent(QMouseEvent *);
    SystemState status;

signals:
    void clicked();
};

#endif // STATEWIDGET_H
