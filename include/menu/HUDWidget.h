#ifndef HUDWIDGET_H
#define HUDWIDGET_H

#include <QWidget>
#include "include/enum/Enum.h"

namespace Ui
{
	class HUDWidget;
	class HUDWidgetTimer;
}

class Bonus;
class SpecialBonus;
class GameEngine;
class QProgressBar;
class QLabel;
class BonusWidget;

class HUDWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HUDWidget(GameEngine* ge, QWidget *parent = 0);
    ~HUDWidget();
    void setPlayerName(Shooter _player, QString _name);
    void setPlayerHP(Shooter _player, int _hp);
    void setPlayerShield(Shooter _player, int _shield);
    void setPlayerScore(Shooter _player, int _score);
    void setNormalBonus(Shooter _player, Bonus* _type);
    void setSpecialBonus(Shooter _player, SpecialBonus* _type);
    void setTimer(QTime _time);
    void activateBonus(Shooter _player, Action _typeBonus);
    void deactivateBonus(Shooter _player, Action _typeBonus);
    BonusState getBonusState(Shooter _player, Action _typeBonus);
    void startTimer();

private:
	QLabel* p1_lblHP;
	QLabel* p1_lblShield;
	QLabel* p1_name;
	QProgressBar* p1_hp;
	QProgressBar* p1_shield;
	BonusWidget* p1_normalBonus;
	BonusWidget* p1_specialBonus;
	QLabel* p1_pts;

	QLabel* p2_lblHP;
	QLabel* p2_lblShield;
	QLabel* p2_name;
	QProgressBar* p2_hp;
	QProgressBar* p2_shield;
	BonusWidget* p2_normalBonus;
	BonusWidget* p2_specialBonus;
	QLabel* p2_pts;

	QLabel* timer;

	Ui::HUDWidget* hudWidget;
	Ui::HUDWidgetTimer* hudWidgetTimer;
	GameMode mode;
};

#endif // HUDWIDGET_H
