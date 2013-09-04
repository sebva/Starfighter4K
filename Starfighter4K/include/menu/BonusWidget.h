#ifndef BONUSWIDGET_H
#define BONUSWIDGET_H

#include "include/enum/Enum.h"

class QWidget;
class QLabel;
class QTime;
class QElapsedTimer;
class QTimer;
class Bonus;
class SpecialBonus;
class BonusProjectile;

class BonusWidget : public QLabel
{
    Q_OBJECT
    
public:
    BonusWidget(QWidget *parent = 0);
    ~BonusWidget();
    void setBonus(Bonus* bonus);
    void setBonus(SpecialBonus* bonus);
    void setBonus(BonusProjectile* bonus);
    BonusState getState() { return state; }
	void startTimer();

protected:
    void paintEvent(QPaintEvent *event);

private:
	bool hasStarted;
    QTime elapsed;
    QElapsedTimer pauseTime;
    QTimer clock;
    int cooldown; // (ms)
    int bonusDuration; // (ms), -1 = Limited usages
    int initialActivations;
    int remainingActivations;
    BonusState state;

public slots:
    void activate();
    void deactivate();
    void updateWidget();
    void pause(bool);
};

#endif // BONUSWIDGET_H
