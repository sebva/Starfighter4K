#include "include/menu/ConnectDialog.h"
#include "include/kinect/qkinect.h"
#include "ui_ConnectDialog.h"
#include <thread>

ConnectDialog::ConnectDialog(WiimoteEngine* wiimoteEngine, QKinect* kinect, QWidget *parent) :
    QDialog(parent),
    wiimoteEngine(wiimoteEngine),
	kinect(kinect),
	greenScreen(nullptr),
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
		wiimoteEngine->startAccel();
		wiimoteEngine->start();
       ui->wiimote->setStatus(SystemStateReady);
    }
    else
        ui->wiimote->setStatus(SystemStateFailed);

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
	{
		greenScreen->close();
		delete greenScreen;
		greenScreen = nullptr;
		ui->calibration->setStatus(SystemStateReady);
	}
	else if(greenScreen == nullptr)
	{
		QPixmap pixmap(5000, 5000);
		pixmap.fill(QColor("#09741b"));
		greenScreen = new QSplashScreen(pixmap);
		greenScreen->showFullScreen();
		greenScreen->setFont(QFont("Helvetica neue", 35));
		greenScreen->showMessage(tr("Calibration in progess..."), Qt::AlignCenter);
		greenScreen->raise();
		kinect->calibrate();
	}

	connect(kinect, SIGNAL(calibrated()), this, SLOT(performCalibration()));

    checkAndClose();
}

void ConnectDialog::checkAndClose()
{
    int statuses = ui->kinect->getStatus() + ui->wiimote->getStatus() + ui->calibration->getStatus();
    if(statuses == SystemStateReady * 3)
        accept();
}
