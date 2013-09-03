#include "include/menu/Overlay.h"

Overlay::Overlay(QWidget *parent)
    : QWidget(parent)
{
    setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Overlay::setHands(QPair<QPoint, QPoint> hands)
{
	hand1 = hands.first;
	hand2 = hands.second;

	update();
}

void Overlay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
	painter.drawEllipse(hand1, 50, 50);
	painter.setBrush(Qt::green);
	painter.drawEllipse(hand2, 50, 50);
}
