#ifndef HUDWIDGET_H
#define HUDWIDGET_H

#include <QDockWidget>
#include "include/enum/Enum.h"

namespace Ui {
class HUDWidget;
}

class Bonus;
class SpecialBonus;

class HUDWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit HUDWidget(QWidget *parent = 0, GameMode _mode = DeathMatch);
    ~HUDWidget();
    void setPlayerName(Shooter _player, QString _name);
    void setPlayerHP(Shooter _player, int _hp);
    void setPlayerShield(Shooter _player, int _shield);
    void setPlayerScore(Shooter _player, int _score);
    void setNormalBonus(Shooter _player, Bonus* _type);
    void setSpecialBonus(Shooter _player, SpecialBonus* _type);
    void setTimer(QTime _time);
    void deactivateBonus(Shooter _player, Action _typeBonus);
    
private:
    Ui::HUDWidget *ui;
};

#endif // HUDWIDGET_H
