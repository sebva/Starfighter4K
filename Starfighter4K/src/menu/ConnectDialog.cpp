#include "include/menu/ConnectDialog.h"
#include "ui_ConnectDialog.h"

ConnectDialog::ConnectDialog(WiimoteEngine* wiimoteEngine, QWidget *parent) :
    QDialog(parent),
    wiimoteEngine(wiimoteEngine),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    ui->wiimote->setSystemName(tr("Wiimote"));
    ui->kinect->setSystemName(tr("Kinect"));
    ui->calibration->setSystemName(tr("Calibration"));

    connect(ui->wiimote, SIGNAL(clicked()), this, SLOT(connectWiimotes()));
    connect(ui->kinect, SIGNAL(clicked()), this, SLOT(connectKinect()));
    connect(ui->calibration, SIGNAL(clicked()), this, SLOT(performCalibration()));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::connectWiimotes()
{
    ui->wiimote->setStatus(SystemStateLoading);
    int wiimotes = wiimoteEngine->findWiimotes();
    qDebug() << wiimotes;
    if(wiimotes >= 2)
    {
        wiimoteEngine->connectWiimotes();
        ui->wiimote->setStatus(SystemStateReady);
    }
    else
        ui->wiimote->setStatus(SystemStateFailed);

    checkAndClose();
}

void ConnectDialog::connectKinect()
{
    // TODO
    ui->kinect->setStatus(SystemStateReady);

    checkAndClose();
}

void ConnectDialog::performCalibration()
{
    // TODO
    if(ui->kinect->getStatus() != SystemStateReady)
        return;

    ui->calibration->setStatus(SystemStateReady);

    checkAndClose();
}

void ConnectDialog::checkAndClose()
{
    int statuses = ui->kinect->getStatus() + ui->wiimote->getStatus() + ui->calibration->getStatus();
    if(statuses == SystemStateReady * 3)
    {
        setResult(QDialog::Accepted);
        close();
    }
}
