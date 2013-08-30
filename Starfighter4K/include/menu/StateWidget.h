#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>

namespace Ui {
class StateWidget;
}

enum SystemState {
    SystemStateReady = 1,
    SystemStateLoading = 2,
    SystemStateFailed = 3
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
    QMovie* mov;

signals:
    void clicked();
};

#endif // STATEWIDGET_H
