#include "include/menu/AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->textBrowser->setSource(tr("qrc:/strings/about"));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_btnBack_clicked()
{
    this->close();
    delete this;
}
