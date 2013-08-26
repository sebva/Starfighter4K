#include "include/menu/HUDWidget.h"
#include "ui_HUDWidget.h"
#include "include/config/Define.h"
#include "include/game/Bonus.h"
#include "include/game/SpecialBonus.h"
#include "include/game/BonusProjectile.h"
#include "include/menu/BonusWidget.h"

HUDWidget::HUDWidget(QWidget *parent, GameMode _mode) :
    QDockWidget(parent),
    ui(new Ui::HUDWidget)
{
    ui->setupUi(this);
    // Remove the title bar
    setTitleBarWidget(new QWidget(this));

    if(_mode == Timer)
    {
        ui->p1_hp->setVisible(false);
        ui->p2_hp->setVisible(false);
        ui->p1_shield->setVisible(false);
        ui->p2_shield->setVisible(false);
        ui->p1_lblHP->setVisible(false);
        ui->p2_lblHP->setVisible(false);
        ui->p1_lblShield->setVisible(false);
        ui->p2_lblShield->setVisible(false);
    }
    else if(_mode == DeathMatch)
    {
        ui->p1_pts->setVisible(false);
        ui->p2_pts->setVisible(false);
        ui->timer->setVisible(false);
    }
}

HUDWidget::~HUDWidget()
{
    delete ui;
}

void HUDWidget::setPlayerName(Shooter _player, QString _name)
{
    QLabel* lbl = 0;
    switch(_player)
    {
        case Player1:
            lbl = ui->p1_name;
            break;
        case Player2:
            lbl = ui->p2_name;
            break;
        default:
            qDebug() << "The HUD is for players only !";
            return;
    }

    lbl->setText(_name);
}

void HUDWidget::setPlayerHP(Shooter _player, int _hp)
{
    QProgressBar* prg = 0;
    switch(_player)
    {
        case Player1:
            prg = ui->p1_hp;
            break;
        case Player2:
            prg = ui->p2_hp;
            break;
        default:
            qDebug() << "The HUD is for players only !";
            return;
    }

    prg->setValue(_hp);
}

void HUDWidget::setPlayerShield(Shooter _player, int _shield)
{
    QProgressBar* prg = 0;
    switch(_player)
    {
        case Player1:
            prg = ui->p1_shield;
            break;
        case Player2:
            prg = ui->p2_shield;
            break;
        default:
            qDebug() << "The HUD is for players only !";
            return;
    }

    prg->setValue(_shield);
}

void HUDWidget::setPlayerScore(Shooter _player, int _score)
{
    QLabel* pts = 0;
    switch(_player)
    {
        case Player1:
            pts = ui->p1_pts;
            break;
        case Player2:
            pts = ui->p2_pts;
            break;
        default:
            qDebug() << "The HUD is for players only !";
            return;
    }

    pts->setText(QString::number(_score));
}

void HUDWidget::setNormalBonus(Shooter _player, Bonus* _bonus)
{
    if(_player == Player1)
        ui->p1_normalBonus->setBonus(_bonus);
    else if(_player == Player2)
        ui->p2_normalBonus->setBonus(_bonus);
}

void HUDWidget::setSpecialBonus(Shooter _player, SpecialBonus* _bonus)
{
    if(_player == Player1)
        ui->p1_specialBonus->setBonus(_bonus); // TODO: cooldown
    else
        ui->p2_specialBonus->setBonus(_bonus);
}

void HUDWidget::activateBonus(Shooter _player, Action _typeBonus)
{
    if(_typeBonus == NormalBonus)
    {
        if(_player == Player1)
            ui->p1_normalBonus->activate();
        else if(_player == Player2)
            ui->p2_normalBonus->activate();
    }
    else if(_typeBonus == aSpecialBonus)
    {
        if(_player == Player1)
            ui->p1_specialBonus->activate();
        else if(_player == Player2)
            ui->p2_specialBonus->activate();
    }
}

void HUDWidget::deactivateBonus(Shooter _player, Action _typeBonus)
{
    if(_typeBonus == NormalBonus)
    {
        if(_player == Player1)
            ui->p1_normalBonus->deactivate();
        else if(_player == Player2)
            ui->p2_normalBonus->deactivate();
    }
    else if(_typeBonus == aSpecialBonus)
    {
        if(_player == Player1)
            ui->p1_specialBonus->deactivate();
        else if(_player == Player2)
            ui->p2_specialBonus->deactivate();
    }
}

void HUDWidget::setTimer(QTime _time)
{
    ui->timer->setText(_time.toString("mm:ss"));
}
