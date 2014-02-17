#include "include/menu/StateWidget.h"
#include "ui_StateWidget.h"

StateWidget::StateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StateWidget)
{
    ui->setupUi(this);

    setStatus(SystemStateUninitialized);
}

StateWidget::~StateWidget()
{
    delete ui;
}

SystemState StateWidget::getStatus()
{
    return status;
}

void StateWidget::setStatus(SystemState status)
{
    QPalette p(palette());
    this->status = status;

    switch(status)
    {
    case SystemStateReady:
        p.setColor(QPalette::Background, QColor("#2ecc71"));
        ui->systemStatus->setPixmap(QPixmap(":/images/menu/v"));
        break;
    case SystemStateFailed:
        p.setColor(QPalette::Background, QColor("#c0392b"));
        ui->systemStatus->setPixmap(QPixmap(":/images/menu/x"));
        break;
	case SystemStateUninitialized:
        p.setColor(QPalette::Background, QColor("#95a5a6"));
		ui->systemStatus->setPixmap(QPixmap());
        break;
    }

    setAutoFillBackground(true);
    setPalette(p);
}

void StateWidget::setSystemName(QString name)
{
    ui->systemName->setText(name);
}

void StateWidget::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}
