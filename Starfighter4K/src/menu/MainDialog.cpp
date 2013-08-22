#include "include/menu/MainDialog.h"
#include "include/menu/OptionsDialog.h"
#include "include/menu/NewGameDialog.h"
#include "include/menu/AboutDialog.h"
#include "ui_MainDialog.h"
#include "include/engine/GameEngine.h"
#include "include/engine/DisplayEngine.h"
#include "include/config/Define.h"
#include "includE/engine/WiimoteEngine.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::MainDialog), we(new WiimoteEngine(this))
{
    //*
    we->connectWiimotes();
    we->startAccel();
    we->start();
    //*/

    ui->setupUi(this);
    setWindowIcon(QIcon(ICON_TASKBAR));
    ge = 0;
    ngd = 0;

    QMediaPlaylist* pl = new QMediaPlaylist(this);
    pl->addMedia(QMediaContent(QUrl::fromLocalFile("./sounds/menu.mp3")));
    pl->setPlaybackMode(QMediaPlaylist::Loop);
    menuMusic = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    menuMusic->setPlaylist(pl);
    menuMusic->play();
}

MainDialog::~MainDialog()
{
    delete ui;
    we->stop();
    delete we;
}

void MainDialog::on_btnPlay_clicked()
{
    ngd = new NewGameDialog(this);
    ngd->exec();
}

void MainDialog::on_btnOptions_clicked()
{
    OptionsDialog *od = new OptionsDialog(this);
    od->exec();
}

void MainDialog::on_btnAbout_clicked()
{
    AboutDialog *ad = new AboutDialog(this);
    ad->exec();
}

void MainDialog::setGameEngine(GameEngine *ge)
{
    if(ge != 0)
        this->ge = ge;
}

void MainDialog::stopMusic()
{
    menuMusic->stop();
}

void MainDialog::endGame()
{
    ge->deleteLater();
    ngd->deleteLater();
    ngd=0;
    ge=0;

    menuMusic->play();
}
