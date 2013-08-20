#include "include/menu/NewGameDialog.h"
#include "include/menu/MainDialog.h"
#include "ui_NewGameDialog.h"
#include "include/engine/GameEngine.h"
#include "include/config/Define.h"

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::NewGameDialog)
{
    md = (MainDialog *)parent;

    ui->setupUi(this);

    ui->cbbGametype->addItem(tr("Deathmatch"), QVariant(DeathMatch));
    ui->cbbGametype->addItem(tr("Timer"), QVariant(Timer));

    ui->cbbP1ship->addItem("Bermuder", QVariant(SpaceshipType1));
    ui->cbbP1ship->addItem("Speeder", QVariant(SpaceshipType2));
    ui->cbbP1ship->addItem("Blaster", QVariant(SpaceshipType3));
    ui->cbbP2ship->addItem("Bermuder", QVariant(SpaceshipType1));
    ui->cbbP2ship->addItem("Speeder", QVariant(SpaceshipType2));
    ui->cbbP2ship->addItem("Blaster", QVariant(SpaceshipType3));

    if(RESISTANCE_1 > RESISTANCE_2)
    {
        if(RESISTANCE_1 > RESISTANCE_3)
            resMax = RESISTANCE_1;
        else
            resMax = RESISTANCE_3;
    }
    else
    {
        if(RESISTANCE_2 > RESISTANCE_3)
            resMax = RESISTANCE_2;
        else
            resMax = RESISTANCE_3;
    }

    if(SPEED_1 > SPEED_2)
    {
        if(SPEED_1 > SPEED_3)
            speedMax = SPEED_1;
        else
            speedMax = SPEED_3;
    }
    else
    {
        if(SPEED_2 > SPEED_3)
            speedMax = SPEED_2;
        else
            speedMax = SPEED_3;
    }

    updateSpaceshipsStats();
}

NewGameDialog::~NewGameDialog()
{
    delete ui;
}

void NewGameDialog::on_btnBack_clicked()
{
    close();
    delete this;
}

void NewGameDialog::on_btnStart_clicked()
{
    GameMode gameMode = (GameMode)(ui->cbbGametype->itemData(ui->cbbGametype->currentIndex()).toInt());
    int duration = ui->sbxDuration->value();
    SpaceshipType player1 = (SpaceshipType)(int)(ui->cbbP1ship->itemData(ui->cbbP1ship->currentIndex()).toInt());
    SpaceshipType player2 = (SpaceshipType)(int)(ui->cbbP2ship->itemData(ui->cbbP2ship->currentIndex()).toInt());
    int difficulty = 0;
    difficulty |= ((ui->cbxAlien->checkState() / Qt::Checked) * AlienMothership);
    difficulty |= ((ui->cbxAsteroid->checkState() / Qt::Checked) * Asteroids);
    difficulty |= ((ui->cbxSatellite->checkState() / Qt::Checked) * Satellites);
    difficulty |= ((ui->cbxSupernova->checkState() / Qt::Checked) * Supernovae);

    if(difficulty == Supernovae)
    {
        QMessageBox::warning(this, tr("Supernovae only"), tr("Sorry, you cannot play with supernovae only."));
    }
    else
    {
        GameEngine *ge = new GameEngine(gameMode, duration, player1, player2, difficulty, this);
        md->setGameEngine(ge);
        connect(ge, SIGNAL(endGame()), md, SLOT(endGame()));
        md->stopMusic();
        close();
    }
}

void NewGameDialog::on_cbbGametype_currentIndexChanged(int index)
{
    if(ui->cbbGametype->itemData(index) == DeathMatch)
    {
        ui->sbxDuration->setEnabled(false);
    }
    else if(ui->cbbGametype->itemData(index) == Timer)
    {
        ui->sbxDuration->setEnabled(true);
    }
}

void NewGameDialog::setPixmapForLabelWithSpaceshipType(SpaceshipType sType, QLabel *lbl)
{
    if(lbl == NULL)
        return;

    switch(sType)
    {
    case SpaceshipType1:
        lbl->setPixmap(QPixmap(PICTURE_SPACESHIP_1));
        break;
    case SpaceshipType2:
        lbl->setPixmap(QPixmap(PICTURE_SPACESHIP_2));
        break;
    case SpaceshipType3:
        lbl->setPixmap(QPixmap(PICTURE_SPACESHIP_3));
        break;
    }
}

void NewGameDialog::updateSpaceshipsStats()
{
    SpaceshipType player1 = (SpaceshipType)(int)(ui->cbbP1ship->itemData(ui->cbbP1ship->currentIndex()).toInt());
    SpaceshipType player2 = (SpaceshipType)(int)(ui->cbbP2ship->itemData(ui->cbbP2ship->currentIndex()).toInt());

    setPixmapForLabelWithSpaceshipType(player1, ui->imgP1);
    setPixmapForLabelWithSpaceshipType(player2, ui->imgP2);

    int res1 = 0, speed1 = 0, res2 = 0, speed2 = 0;

    switch(player1)
    {
    case SpaceshipType1:
        res1 = RESISTANCE_1;
        speed1 = SPEED_1;
        break;
    case SpaceshipType2:
        res1 = RESISTANCE_2;
        speed1 = SPEED_2;
        break;
    case SpaceshipType3:
        res1 = RESISTANCE_3;
        speed1 = SPEED_3;
        break;
    }
    switch(player2)
    {
    case SpaceshipType1:
        res2 = RESISTANCE_1;
        speed2 = SPEED_1;
        break;
    case SpaceshipType2:
        res2 = RESISTANCE_2;
        speed2 = SPEED_2;
        break;
    case SpaceshipType3:
        res2 = RESISTANCE_3;
        speed2 = SPEED_3;
        break;
    }

    ui->resP1->setValue((res1 / (double)resMax) * 100.0);
    ui->resP2->setValue((res2 / (double)resMax) * 100.0);
    ui->speedP1->setValue((speed1 / (double)speedMax) * 100.0);
    ui->speedP2->setValue((speed2 / (double)speedMax) * 100.0);
}

void NewGameDialog::on_cbbP1ship_currentIndexChanged(int index)
{
    updateSpaceshipsStats();
}

void NewGameDialog::on_cbbP2ship_currentIndexChanged(int index)
{
    updateSpaceshipsStats();
}
