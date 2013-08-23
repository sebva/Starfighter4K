#include "include/menu/BonusWidget.h"
#include "include/game/BonusProjectile.h"
#include "include/game/Bonus.h"
#include "include/game/SpecialBonus.h"
#include "include/config/Define.h"
#include "include/stable.h"

BonusWidget::BonusWidget(QWidget *parent)
    : QLabel(parent), cooldown(-1), state(NoBonus), bonusDuration(-1)
{
    setPixmap(QPixmap(IMAGE_BONUS));

    clock.setInterval(100);
    clock.setSingleShot(false);
    connect(&clock, SIGNAL(timeout()), this, SLOT(updateWidget()));
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
        elapsed.start();

    state = Activated;
}

void BonusWidget::deactivate()
{
    if(cooldown == -1)
    {
        setPixmap(QPixmap(IMAGE_BONUS));
        state = NoBonus;
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

    switch(type)
    {
    case TypeBonusHP:
        setPixmap(QPixmap(IMAGE_BONUS_HEALTH));
        break;
    case TypeBonusInvicibility:
        setPixmap(QPixmap(IMAGE_BONUS_INVICIBILITY));
        break;
    case TypeBonusShield:
        setPixmap(QPixmap(IMAGE_BONUS_SHIELD));
        break;
    default:
        setPixmap(QPixmap(IMAGE_BONUS));
        return;
    }

    state = Ready;
}

void BonusWidget::setBonus(BonusProjectile *bonus)
{
    TypeBonus type = bonus->getTypeBonus();

    switch(type)
    {
    case TypeBonusProjectileCross:
        setPixmap(QPixmap(IMAGE_BONUS_PROJ_CROSS));
        break;
    case TypeBonusProjectileSimple:
        setPixmap(QPixmap(IMAGE_BONUS_PROJ_SIMPLE));
        break;
    case TypeBonusProjectileV:
        setPixmap(QPixmap(IMAGE_BONUS_PROJ_V));
        break;
    default:
        setPixmap(QPixmap(IMAGE_BONUS));
        return;
    }

    bonusDuration = bonus->getExpiration();
    state = Ready;
}

void BonusWidget::setBonus(SpecialBonus *bonus, int cooldown)
{
    this->cooldown = cooldown;

    TypeSpecialBonus type = bonus->getTypeBonus();
    switch(type)
    {
    case TypeSpecialBonusFreeze:
        setPixmap(QPixmap(IMAGE_BONUS_FREEZE));
        break;
    case TypeSpecialBonusAntiGravity:
        // TODO: Create the image
        //setPixmap(QPixmap(IMAGE_BONUS_ANTIGRAVITY));
        //break;
    case TypeSpecialBonusGuidedMissile:
        // TODO: Create the image
        //setPixmap(QPixmap(IMAGE_BONUS_GUIDEDMISSILE));
        //break;
    case TypeSpecialBonusOmnidirectionalShot:
        // TODO: Create the image
        //setPixmap(QPixmap(IMAGE_BONUS_OMNIDIRECTIONALSHOT));
        //break;
    case TypeSpecialBonusTrackingMissile:
        // TODO: Create the image
        //setPixmap(QPixmap(IMAGE_BONUS_TRACKINGMISSILE));
        //break;
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

    if(state == Cooldown || state == Activated && bonusDuration != -1)
    {
        QPainter p(this);
        p.setBrush(QBrush(QColor(0, 0, 0, 127)));

        const int offset = 59;
        QRect r(rect().left() + offset, rect().top() + offset, rect().width() - offset*2, rect().height() - offset*2);
        double percent;
        if(state == Cooldown)
            percent = (cooldown - elapsed.elapsed()) / cooldown * 100.0;
        else
            percent = elapsed.elapsed() / bonusDuration * 100.0;
        p.drawPie(r, 90 * 16, 90.0 + -1.0 * percent * 3.6 * 16.0);
    }
}

void BonusWidget::updateWidget()
{
    if(state == Activated && elapsed.hasExpired(bonusDuration))
        deactivate();
    else if(state == Cooldown && elapsed.hasExpired(cooldown))
        state = Ready;

    repaint();
}
