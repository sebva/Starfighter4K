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

    Settings& s = Settings::getGlobalSettings();
    ui->ledP1name->setText(s.playerOneName());
    ui->ledP2name->setText(s.playerTwoName());

    ui->sliderMusicVolume->setValue(s.musicVolume());
    ui->sliderSoundEffectsVolume->setValue(s.soundEffectsVolume());

    int index = (s.HUDArea() == Qt::BottomDockWidgetArea) ? 0 : 1;
    ui->hudArea->setCurrentIndex(index);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::on_btnBack_clicked()
{
    this->close();
    delete this;
}

void OptionsDialog::on_btnSave_clicked()
{
    Settings& s = Settings::getGlobalSettings();

    s.setPlayerOneName(ui->ledP1name->text());
    s.setPlayerTwoName(ui->ledP2name->text());

    s.setMusicVolume(ui->sliderMusicVolume->value());
    s.setSoundEffectsVolume(ui->sliderSoundEffectsVolume->value());

    int index = ui->hudArea->currentIndex();
    s.setHUDArea(index == 0 ? Qt::BottomDockWidgetArea : Qt::TopDockWidgetArea);

    QMessageBox::information(this, tr("Saved"), tr("The settings were successfully saved"));
    this->close();

    delete this;
}

