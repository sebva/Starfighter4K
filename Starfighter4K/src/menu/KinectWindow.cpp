#include "include/menu/KinectWindow.h"
#include "ui_KinectWindow.h"

KinectWindow::KinectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KinectWindow)
{
    ui->setupUi(this);

    ui->scrollText->setText("The quick brown fox jumps over the lazy dog.");

    timer.setHMS(0, 2, 0);
    updateTimerDisplay();
}

KinectWindow::~KinectWindow()
{
    delete ui;
}

void KinectWindow::on_btnGame_clicked()
{
    ui->stack->setCurrentWidget(ui->mode);
}

void KinectWindow::on_btnDeathmatch_clicked()
{
    ui->stack->setCurrentWidget(ui->spaceshipsSelection);
}

void KinectWindow::on_btnTimer_clicked()
{
    ui->stack->setCurrentWidget(ui->timerSelect);
}

void KinectWindow::on_btnValidateTime_clicked()
{

    ui->stack->setCurrentWidget(ui->spaceshipsSelection);
}

void KinectWindow::on_btnPlus_clicked()
{
    timer = timer.addSecs(30);
    updateTimerDisplay();
}

void KinectWindow::on_btnMinus_clicked()
{
    timer = timer.addSecs(-30);
    updateTimerDisplay();
}

void KinectWindow::updateTimerDisplay()
{
    ui->lblTime->setText(timer.toString());
    ui->btnValidateTime->setEnabled(timer != QTime(0, 0));
}

void KinectWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QWidget* cur = ui->stack->currentWidget();

        if(cur == ui->mode)
            ui->stack->setCurrentWidget(ui->home);
        else if(cur == ui->timerSelect)
            ui->stack->setCurrentWidget(ui->mode);
        else if(cur == ui->spaceshipsSelection)
            ui->stack->setCurrentWidget(ui->mode);
        else if(cur == ui->bonusSelection)
            ui->stack->setCurrentWidget(ui->spaceshipsSelection);
    }
}
