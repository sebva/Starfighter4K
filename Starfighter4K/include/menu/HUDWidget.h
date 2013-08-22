#ifndef HUDWIDGET_H
#define HUDWIDGET_H

#include <QDockWidget>
#include "include/enum/Enum.h"

namespace Ui {
class HUDWidget;
}

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
    void setNormalBonus(Shooter _player, TypeBonus _type);
    void setSpecialBonus(Shooter _player, TypeSpecialBonus _type);
    void setTimer(QTime _time);
    
private:
    Ui::HUDWidget *ui;
};

#endif // HUDWIDGET_H
