#include "include/menu/HUDWidget.h"
#include "ui_HUDWidget.h"
#include "ui_HUDWidgetTimer.h"
#include "include/config/Define.h"
#include "include/game/Bonus.h"
#include "include/game/SpecialBonus.h"
#include "include/game/BonusProjectile.h"
#include "include/menu/BonusWidget.h"
#include "include/engine/GameEngine.h"

HUDWidget::HUDWidget(GameEngine* ge, QWidget *parent) :
	QWidget(parent),hudWidget(new Ui::HUDWidget),hudWidgetTimer(new Ui::HUDWidgetTimer),mode(ge->getGameMode())
{
    if(mode == DeathMatch)
    {
		hudWidget->setupUi(this);
		p1_lblHP = hudWidget->p1_lblHP;
		p1_lblShield = hudWidget->p1_lblShield;
		p1_hp = hudWidget->p1_hp;
		p1_shield = hudWidget->p1_shield;

		p2_lblHP = hudWidget->p2_lblHP;
		p2_lblShield = hudWidget->p2_lblShield;
		p2_hp = hudWidget->p2_hp;
		p2_shield = hudWidget->p2_shield;

		p1_name = hudWidget->p1_name;
		p1_normalBonus =  hudWidget->p1_normalBonus;
		p1_specialBonus =  hudWidget->p1_specialBonus;

		p2_name = hudWidget->p2_name;
		p2_normalBonus =  hudWidget->p2_normalBonus;
		p2_specialBonus =  hudWidget->p2_specialBonus;
    }
    else if(mode == Timer)
    {
		hudWidgetTimer->setupUi(this);
		p1_pts = hudWidgetTimer->p1_pts;
		p2_pts = hudWidgetTimer->p2_pts;
		timer = hudWidgetTimer->timer;

		p1_name = hudWidgetTimer->p1_name;
		p1_normalBonus =  hudWidgetTimer->p1_normalBonus;
		p1_specialBonus =  hudWidgetTimer->p1_specialBonus;

		p2_name = hudWidgetTimer->p2_name;
		p2_normalBonus =  hudWidgetTimer->p2_normalBonus;
		p2_specialBonus =  hudWidgetTimer->p2_specialBonus;
    }

	connect(ge, SIGNAL(signalPause(bool)), p1_normalBonus, SLOT(pause(bool)));
	connect(ge, SIGNAL(signalPause(bool)), p2_normalBonus, SLOT(pause(bool)));
	connect(ge, SIGNAL(signalPause(bool)), p1_specialBonus, SLOT(pause(bool)));
	connect(ge, SIGNAL(signalPause(bool)), p2_specialBonus, SLOT(pause(bool)));
}

HUDWidget::~HUDWidget()
{
    delete hudWidget;
	delete hudWidgetTimer;
}

void HUDWidget::setPlayerName(Shooter _player, QString _name)
{
    QLabel* lbl = 0;
    switch(_player)
    {
        case Player1:
            lbl = p1_name;
            break;
        case Player2:
            lbl = p2_name;
            break;
        default:
            qWarning() << "The HUD is for players only !";
            return;
    }

    lbl->setText(_name);
}

void HUDWidget::setPlayerHP(Shooter _player, int _hp)
{
	if(mode != DeathMatch)
		return;
    QProgressBar* prg = 0;
    switch(_player)
    {
        case Player1:
            prg = p1_hp;
            break;
        case Player2:
            prg = p2_hp;
            break;
        default:
            qWarning() << "The HUD is for players only !";
            return;
    }

    prg->setValue(_hp);
}

void HUDWidget::setPlayerShield(Shooter _player, int _shield)
{
	if(mode != DeathMatch)
		return;
    QProgressBar* prg = 0;
    switch(_player)
    {
        case Player1:
            prg = p1_shield;
            break;
        case Player2:
            prg = p2_shield;
            break;
        default:
            qWarning() << "The HUD is for players only !";
            return;
    }

    prg->setValue(_shield);
}

void HUDWidget::setPlayerScore(Shooter _player, int _score)
{
	if(mode != Timer)
		return;
    QLabel* pts = 0;
    switch(_player)
    {
        case Player1:
            pts = p1_pts;
            break;
        case Player2:
            pts = p2_pts;
            break;
        default:
            qWarning() << "The HUD is for players only !";
            return;
    }

    pts->setText(QString::number(_score));
}

void HUDWidget::setNormalBonus(Shooter _player, Bonus* _bonus)
{
    if(_player == Player1)
        p1_normalBonus->setBonus(_bonus);
    else if(_player == Player2)
        p2_normalBonus->setBonus(_bonus);
}

void HUDWidget::setSpecialBonus(Shooter _player, SpecialBonus* _bonus)
{
    if(_player == Player1)
        p1_specialBonus->setBonus(_bonus); // TODO: cooldown
    else
        p2_specialBonus->setBonus(_bonus);
}

void HUDWidget::activateBonus(Shooter _player, Action _typeBonus)
{
    if(_typeBonus == NormalBonus)
    {
        if(_player == Player1)
            p1_normalBonus->activate();
        else if(_player == Player2)
            p2_normalBonus->activate();
    }
    else if(_typeBonus == aSpecialBonus)
    {
        if(_player == Player1)
            p1_specialBonus->activate();
        else if(_player == Player2)
            p2_specialBonus->activate();
    }
}

void HUDWidget::deactivateBonus(Shooter _player, Action _typeBonus)
{
    if(_typeBonus == NormalBonus)
    {
        if(_player == Player1)
            p1_normalBonus->deactivate();
        else if(_player == Player2)
            p2_normalBonus->deactivate();
    }
    else if(_typeBonus == aSpecialBonus)
    {
        if(_player == Player1)
            p1_specialBonus->deactivate();
        else if(_player == Player2)
            p2_specialBonus->deactivate();
    }
}

BonusState HUDWidget::getBonusState(Shooter _player, Action _typeBonus)
{
    if(_typeBonus == NormalBonus)
    {
        if(_player == Player1)
            return p1_normalBonus->getState();
        else if(_player == Player2)
            return p2_normalBonus->getState();
    }
    else if(_typeBonus == aSpecialBonus)
    {
        if(_player == Player1)
            return p1_specialBonus->getState();
        else if(_player == Player2)
            return p2_specialBonus->getState();
    }
    return BonusStateNoBonus;
}

void HUDWidget::setTimer(QTime _time)
{
    timer->setText(_time.toString("mm:ss"));
}

void HUDWidget::startTimer()
{
	p1_specialBonus->startTimer();
	p2_specialBonus->startTimer();
	p1_normalBonus->startTimer();
	p2_normalBonus->startTimer();
}