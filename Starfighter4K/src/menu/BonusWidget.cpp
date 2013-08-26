#include "include/menu/BonusWidget.h"
#include "include/game/BonusProjectile.h"
#include "include/game/Bonus.h"
#include "include/game/BonusInvicibility.h"
#include "include/game/SpecialBonus.h"
#include "include/game/SpecialBonusLimitedTime.h"
#include "include/game/SpecialBonusLimitedUsage.h"
#include "include/config/Define.h"
#include "include/stable.h"

BonusWidget::BonusWidget(QWidget *parent)
    : QLabel(parent), cooldown(-1), state(NoBonus), bonusDuration(-1), initialActivations(1), remainingActivations(1)
{
    setPixmap(QPixmap(IMAGE_BONUS));

    clock.setInterval(100);
    clock.setSingleShot(false);
    connect(&clock, SIGNAL(timeout()), this, SLOT(updateWidget()));
    clock.start();
}

BonusWidget::~BonusWidget()
{
    clock.stop();
}

void BonusWidget::activate()
{
    if(state != Ready)
        return;

    if(bonusDuration != -1)
    {
        elapsed.start();
        state = Activated;
    }
    else if(--remainingActivations <= 0)
        deactivate();
}

void BonusWidget::deactivate()
{
    if(cooldown == -1)
    {
        setPixmap(QPixmap(IMAGE_BONUS));
        state = NoBonus;
        bonusDuration = -1;
        remainingActivations = 1;
    }
    else
    {
        elapsed.start();
        state = Cooldown;
    }
}

void BonusWidget::setBonus(Bonus *bonus)
{
    TypeBonus type = bonus->getTypeBonus();
    //qDebug() << "Type : " << type;

    switch(type)
    {
    case TypeBonusHP:
        setPixmap(QPixmap(IMAGE_BONUS_HEALTH));
        break;
    case TypeBonusInvicibility:
        bonusDuration = ((BonusInvicibility*)bonus)->getExpiration();
        setPixmap(QPixmap(IMAGE_BONUS_INVICIBILITY));
        break;
    case TypeBonusShield:
        setPixmap(QPixmap(IMAGE_BONUS_SHIELD));
        break;
    case TypeBonusProjectile:
        setBonus(dynamic_cast<BonusProjectile*>(bonus));
        break;
    default:
        setPixmap(QPixmap(IMAGE_BONUS));
        return;
    }

    state = Ready;
}

void BonusWidget::setBonus(BonusProjectile *bonus)
{
    TypeProjectiles type = bonus->getType();
    //qDebug() << "Type projectile : " << type;

    switch(type)
    {
    case ProjCross:
        setPixmap(QPixmap(IMAGE_BONUS_PROJ_CROSS));
        break;
    case ProjSimple:
        setPixmap(QPixmap(IMAGE_BONUS_PROJ_SIMPLE));
        break;
    case ProjV:
        setPixmap(QPixmap(IMAGE_BONUS_PROJ_V));
        break;
    default:
        setPixmap(QPixmap(IMAGE_BONUS));
        return;
    }

    bonusDuration = bonus->getExpiration();
    //qDebug() << "Duration : " << bonusDuration;
    state = Ready;
}

void BonusWidget::setBonus(SpecialBonus *bonus)
{
    this->cooldown = bonus->getCooldownTime();
    //qDebug() << "Special bonus cooldown : " << cooldown;

    SpecialBonusLimitedTime* sblt = dynamic_cast<SpecialBonusLimitedTime*>(bonus);
    if(sblt)
        this->bonusDuration = sblt->getDuration();
    else
    {
        SpecialBonusLimitedUsage* sblu = dynamic_cast<SpecialBonusLimitedUsage*>(bonus);
        if(sblu)
            remainingActivations = initialActivations = sblu->getInitialActivation();
    }

    TypeSpecialBonus type = bonus->getTypeBonus();
    switch(type)
    {
    case TypeSpecialBonusFreeze:
        setPixmap(QPixmap(IMAGE_BONUS_FREEZE));
        break;
    case TypeSpecialBonusAntiGravity:
        setPixmap(QPixmap(IMAGE_BONUS_ANTIGRAVITY));
        break;
    case TypeSpecialBonusGuidedMissile:
        setPixmap(QPixmap(IMAGE_BONUS_GUIDEDMISSILE));
        break;
    case TypeSpecialBonusOmnidirectionalShot:
        setPixmap(QPixmap(IMAGE_BONUS_ROOTSHOT));
        break;
    case TypeSpecialBonusTrackingMissile:
        setPixmap(QPixmap(IMAGE_BONUS_TRACKINGMISSILE));
        break;
    case TypeSpecialBonusNothing:
    default:
        setPixmap(QPixmap(IMAGE_BONUS));
        break;
    }

    deactivate();
}

void BonusWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    if(state == Cooldown || state == Activated)
    {
        QPainter p(this);
        if(state == Activated)
            p.setBrush(QBrush(QColor(0, 0, 255, 127)));
        else
            p.setBrush(QBrush(QColor(0, 0, 0, 127)));

        const int offset = 59;
        QRect r(rect().left() + offset, rect().top() + offset, rect().width() - offset*2, rect().height() - offset*2);
        double percent;
        if(state == Cooldown)
            percent = (cooldown - elapsed.elapsed()) / (double)cooldown * 100.0;
        else if(state == Activated)
        {
            if(bonusDuration == -1)
                percent = remainingActivations / (double)initialActivations * 100.0;
            else
                percent = elapsed.elapsed() / (double)bonusDuration * 100.0;
        }

        //qDebug() << percent;
        p.drawPie(r, 90 * 16, 90.0 + -1.0 * percent * 3.6 * 16.0);
    }
}

void BonusWidget::updateWidget()
{
    if(state == Activated && bonusDuration != -1 && elapsed.hasExpired(bonusDuration))
        deactivate();
    else if(state == Cooldown && elapsed.hasExpired(cooldown))
        state = Ready;

    repaint();
}
