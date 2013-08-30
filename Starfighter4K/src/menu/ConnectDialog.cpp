#include "include/menu/ConnectDialog.h"
#include "include/kinect/qkinect.h"
#include "ui_ConnectDialog.h"
#include <thread>

ConnectDialog::ConnectDialog(WiimoteEngine* wiimoteEngine, QKinect* kinect, QWidget *parent) :
    QDialog(parent),
    wiimoteEngine(wiimoteEngine),
	kinect(kinect),
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
	
    wiimoteEngine->startAccel();
    wiimoteEngine->start();

    checkAndClose();
}

void ConnectDialog::connectKinect()
{
	if(kinect->startKinect())
		ui->kinect->setStatus(SystemStateReady);

    checkAndClose();
}

void ConnectDialog::performCalibration()
{
    if(ui->kinect->getStatus() != SystemStateReady)
        return;

	if(kinect->isCalibrated())
		ui->calibration->setStatus(SystemStateReady);
	else
		kinect->calibrate();

	connect(kinect, SIGNAL(calibrated()), this, SLOT(performCalibration()));

    checkAndClose();
}

void ConnectDialog::checkAndClose()
{
    int statuses = ui->kinect->getStatus() + ui->wiimote->getStatus() + ui->calibration->getStatus();
    if(statuses == SystemStateReady * 3)
        accept();
}
