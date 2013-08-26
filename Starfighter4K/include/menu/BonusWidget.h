#ifndef BONUSWIDGET_H
#define BONUSWIDGET_H

class QWidget;
class QLabel;
class QElapsedTimer;
class QTimer;
class Bonus;
class SpecialBonus;
class BonusProjectile;

enum BonusState {
    Activated,
    Ready,
    Cooldown,
    NoBonus
};

class BonusWidget : public QLabel
{
    Q_OBJECT
    
public:
    BonusWidget(QWidget *parent = 0);
    ~BonusWidget();
    void setBonus(Bonus* bonus);
    void setBonus(SpecialBonus* bonus);
    void setBonus(BonusProjectile* bonus);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QElapsedTimer elapsed;
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
};

#endif // BONUSWIDGET_H
