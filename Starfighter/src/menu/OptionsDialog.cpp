#include "include/menu/OptionsDialog.h"
#include "include/utils/Settings.h"
#include "ui_OptionsDialog.h"
#include <QMessageBox>
#include "include/enum/Enum.h"
#include "include/menu/SetKeyDialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    inSetting = -1;

    btgKeys = new QButtonGroup(this);
    btgKeys->addButton(ui->btnP1Up, aTop1);
    btgKeys->addButton(ui->btnP2Up, aTop2);
    btgKeys->addButton(ui->btnP1Down, aBottom1);
    btgKeys->addButton(ui->btnP2Down, aBottom2);
    btgKeys->addButton(ui->btnP1Fire, aShoot1);
    btgKeys->addButton(ui->btnP2Fire, aShoot2);

    Settings& s = Settings::getGlobalSettings();
    ui->ledP1name->setText(s.playerOneName());
    ui->ledP2name->setText(s.playerTwoName());

    ui->sliderMusicVolume->setValue(s.musicVolume());
    ui->sliderSoundEffectsVolume->setValue(s.soundEffectsVolume());

    controls = new QMap<Action, Qt::Key>(s.playersControls());

    showKeys();

    connect(btgKeys, SIGNAL(buttonClicked(int)), this, SLOT(keyChange(int)));
}

OptionsDialog::~OptionsDialog()
{
    delete controls;
    delete ui;
}

void OptionsDialog::keyChange(int iKey)
{
    Action key = (Action)iKey;
    inSetting = key;

    SetKeyDialog *skd = new SetKeyDialog(this);
    connect(skd, SIGNAL(keySelected(Qt::Key)), this, SLOT(setKey(Qt::Key)));
    skd->exec();
}

void OptionsDialog::on_btnBack_clicked()
{
    this->close();
    delete this;
}

void OptionsDialog::on_btnSave_clicked()
{
    // Vérification que les toutes les touches sont différentes
    if(QSet<Qt::Key>::fromList(controls->values()).count() < 6)
    {
        QMessageBox::critical(this, tr("Invalid keys"), tr("Two or more keys are set to the same value"));
    }
    else
    {
        Settings& s = Settings::getGlobalSettings();

        s.setPlayerOneName(ui->ledP1name->text());
        s.setPlayerTwoName(ui->ledP2name->text());

        s.setMusicVolume(ui->sliderMusicVolume->value());
        s.setSoundEffectsVolume(ui->sliderSoundEffectsVolume->value());

        s.setPlayersControls(*controls);


        QMessageBox::information(this, tr("Saved"), tr("The settings were successfully saved"));
        this->close();
    }
    delete this;
}

void OptionsDialog::showKeys()
{
        ui->btnP1Up->setText((QString)QKeySequence(controls->value(aTop1)));
        ui->btnP2Up->setText((QString)QKeySequence(controls->value(aTop2)));
        ui->btnP1Down->setText((QString)QKeySequence(controls->value(aBottom1)));
        ui->btnP2Down->setText((QString)QKeySequence(controls->value(aBottom2)));
        ui->btnP1Fire->setText((QString)QKeySequence(controls->value(aShoot1)));
        ui->btnP2Fire->setText((QString)QKeySequence(controls->value(aShoot2)));
}

void OptionsDialog::setKey(Qt::Key key)
{
    controls->insert((Action)inSetting, key);
    inSetting = -1;
    showKeys();
}
