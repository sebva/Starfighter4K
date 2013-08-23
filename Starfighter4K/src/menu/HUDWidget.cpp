#include "include/menu/HUDWidget.h"
#include "ui_HUDWidget.h"
#include "include/config/Define.h"

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

void HUDWidget::setNormalBonus(Shooter _player, TypeBonus _type)
{
    QPixmap pix;
    switch(_type)
    {
    case TypeBonusHP:
        pix = QPixmap(IMAGE_BONUS_HEALTH);
        break;
    case TypeBonusInvicibility:
        pix = QPixmap(IMAGE_BONUS_INVICIBILITY);
        break;
    case TypeBonusShield:
        pix = QPixmap(IMAGE_BONUS_SHIELD);
        break;
    case TypeBonusProjectileCross:
        pix = QPixmap(IMAGE_BONUS_PROJ_CROSS);
        break;
    case TypeBonusProjectileSimple:
        pix = QPixmap(IMAGE_BONUS_PROJ_SIMPLE);
        break;
    case TypeBonusProjectileV:
        pix = QPixmap(IMAGE_BONUS_PROJ_V);
        break;
    case TypeBonusProjectile:
        qDebug() << "[HUD_ERROR] You have to be more precise in order to show a bonus on the HUD";
    case TypeBonusNothing:
    default:
        pix = QPixmap(IMAGE_BONUS);
        break;
    }

    if(_player == Player1)
        ui->p1_normalBonus->setPixmap(pix);
    else if(_player == Player2)
        ui->p2_normalBonus->setPixmap(pix);
}

void HUDWidget::setSpecialBonus(Shooter _player, TypeSpecialBonus _type)
{
    QPixmap pix;
    switch(_type)
    {
    case TypeSpecialBonusFreeze:
        pix = QPixmap(IMAGE_BONUS_FREEZE);
        break;
    case TypeSpecialBonusAntiGravity:
        // TODO: Create the image
        //pix = QPixmap(IMAGE_BONUS_ANTIGRAVITY);
        //break;
    case TypeSpecialBonusGuidedMissile:
        // TODO: Create the image
        //pix = QPixmap(IMAGE_BONUS_GUIDEDMISSILE);
        //break;
    case TypeSpecialBonusOmnidirectionalShot:
        // TODO: Create the image
        //pix = QPixmap(IMAGE_BONUS_OMNIDIRECTIONALSHOT);
        //break;
    case TypeSpecialBonusTrackingMissile:
        // TODO: Create the image
        //pix = QPixmap(IMAGE_BONUS_TRACKINGMISSILE);
        //break;
    case TypeSpecialBonusNothing:
    default:
        pix = QPixmap(IMAGE_BONUS);
        break;
    }

    if(_player == Player1)
        ui->p1_specialBonus->setPixmap(pix);
    else if(_player == Player2)
        ui->p2_specialBonus->setPixmap(pix);
}

void HUDWidget::setTimer(QTime _time)
{
    ui->timer->setText(_time.toString("mm:ss"));
}
