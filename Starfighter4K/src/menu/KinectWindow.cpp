#include "include/menu/KinectWindow.h"
#include "ui_KinectWindow.h"
#include "include/engine/GameEngine.h"
#include "include/engine/WiimoteEngine.h"
#include "include/engine/GameEngine.h"
#include "include/kinect/qkinect.h"
#include "include/utils/Settings.h"
#include "include/config/Define.h"
#include "include/menu/Overlay.h"

KinectWindow::KinectWindow(WiimoteEngine *we, QKinect* kinect, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KinectWindow),
    p1Ship(NoSpaceShip), p2Ship(NoSpaceShip),
    p1Bonus(TypeSpecialBonusNothing), p2Bonus(TypeSpecialBonusNothing),
    we(we), kinect(kinect), ge(0),
	background(":/images/menu/background")
{
    ui->setupUi(this);

	ui->about->setSource(tr("qrc:/strings/about"));

	QSet<QString> namesSet;
	namesSet << NAMES;
	QStringList names(namesSet.toList());

	ui->scrollText->setText(tr("Starfighter 4K - Developed by ").append(names.join(", ")).append(tr(" - Copyright 2013 HE-Arc")));
	ui->scrollText->setSeparator("  +++  ");

    timer.setHMS(0, 2, 0);
    updateTimerDisplay();

	connect(kinect, SIGNAL(newDatas()), this, SLOT(handsMoved()));

	connect(ui->btnBackBonus, SIGNAL(clicked()), this, SLOT(back()));
	connect(ui->btnBackMode, SIGNAL(clicked()), this, SLOT(back()));
	connect(ui->btnBackOptions, SIGNAL(clicked()), this, SLOT(back()));
	connect(ui->btnBackSpaceships, SIGNAL(clicked()), this, SLOT(back()));
	connect(ui->btnBackTimer, SIGNAL(clicked()), this, SLOT(back()));

	QMediaPlaylist* pl = new QMediaPlaylist(this);
    pl->addMedia(QMediaContent(QUrl::fromLocalFile("./sounds/menu.mp3")));
    pl->setPlaybackMode(QMediaPlaylist::Loop);
    menuMusic = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    menuMusic->setPlaylist(pl);
    menuMusic->play();

	//overlay = new Overlay(centralWidget());
}

KinectWindow::~KinectWindow()
{
	delete ui->graphicsView;
    delete ui;
	we->stop();
	delete we;
}

void KinectWindow::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, background);
}

void KinectWindow::resizeEvent(QResizeEvent *event)
{
	//background = QPixmap::fromImage(BlurPushButton::blurred(QImage(":/images/menu/background"), rect(), 20, false));
    //overlay->resize(event->size());

	//update();
    event->accept();
}

void KinectWindow::handsMoved()
{
	QPair<QPoint, QPoint> hands = kinect->getHandsPosition();
	hand1 = hands.first;
	hand2 = hands.second;

	//overlay->setHands(hands);
}

void KinectWindow::on_btnGame_clicked()
{
	ui->graphicsView->escapeGame();
    ui->stack->setCurrentWidget(ui->mode);
}

void KinectWindow::on_btnOptions_clicked()
{
	Settings& s = Settings::getGlobalSettings();
	ui->p1name->setText(s.playerOneName());
	ui->p2name->setText(s.playerTwoName());

	int index = (s.HUDArea() == Qt::TopDockWidgetArea) ? 0 : 1;
    ui->hudPlacement->setCurrentIndex(index);

	ui->stack->setCurrentWidget(ui->options);
}

void KinectWindow::on_btnValidateOptions_clicked()
{
	Settings& s = Settings::getGlobalSettings();
	
    s.setPlayerOneName(ui->p1name->text());
    s.setPlayerTwoName(ui->p2name->text());

    int index = ui->hudPlacement->currentIndex();
    s.setHUDArea(index == 0 ? Qt::TopDockWidgetArea : Qt::BottomDockWidgetArea);

	ui->stack->setCurrentWidget(ui->home);
}

void KinectWindow::on_btnDeathmatch_clicked()
{
    ui->stack->setCurrentWidget(ui->spaceshipsSelection);
    gameMode = DeathMatch;
}

void KinectWindow::on_btnTimer_clicked()
{
    ui->stack->setCurrentWidget(ui->timerSelect);
    gameMode = Timer;
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

void KinectWindow::back()
{
	QWidget* cur = ui->stack->currentWidget();

    if(cur == ui->mode)
	{
		ui->graphicsView->escapeGame();
        ui->stack->setCurrentWidget(ui->home);
	}
	else if(cur == ui->home)
		close();
	else if(cur == ui->options)
		ui->stack->setCurrentWidget(ui->home);
    else if(cur == ui->timerSelect)
        ui->stack->setCurrentWidget(ui->mode);
    else if(cur == ui->spaceshipsSelection)
        ui->stack->setCurrentWidget(ui->mode);
    else if(cur == ui->bonusSelection)
        ui->stack->setCurrentWidget(ui->spaceshipsSelection);
}

void KinectWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
		back();
}

void KinectWindow::validateShips()
{
    if(p1Ship != NoSpaceShip && p2Ship != NoSpaceShip)
        ui->stack->setCurrentWidget(ui->bonusSelection);
}

void KinectWindow::on_btnShip1P1_clicked()
{
    p1Ship = SpaceshipType1;
    validateShips();
}

void KinectWindow::on_btnShip2P1_clicked()
{
    p1Ship = SpaceshipType2;
    validateShips();
}

void KinectWindow::on_btnShip3P1_clicked()
{
    p1Ship = SpaceshipType3;
    validateShips();
}

void KinectWindow::on_btnShip1P2_clicked()
{
    p2Ship = SpaceshipType1;
    validateShips();
}

void KinectWindow::on_btnShip2P2_clicked()
{
    p2Ship = SpaceshipType2;
    validateShips();
}

void KinectWindow::on_btnShip3P2_clicked()
{
    p2Ship = SpaceshipType3;
    validateShips();
}

void KinectWindow::on_btnFreezeP1_clicked()
{
    p1Bonus = TypeSpecialBonusFreeze;
    validateBonus();
}

void KinectWindow::on_btnAntigravityP1_clicked()
{
    p1Bonus = TypeSpecialBonusAntiGravity;
    validateBonus();
}

void KinectWindow::on_btnGuidedP1_clicked()
{
    p1Bonus = TypeSpecialBonusGuidedMissile;
    validateBonus();
}

void KinectWindow::on_btnTrackingP1_clicked()
{
    p1Bonus = TypeSpecialBonusTrackingMissile;
    validateBonus();
}

void KinectWindow::on_btnRootP1_clicked()
{
    p1Bonus = TypeSpecialBonusOmnidirectionalShot;
    validateBonus();
}

void KinectWindow::on_btnFreezeP2_clicked()
{
    p2Bonus = TypeSpecialBonusFreeze;
    validateBonus();
}

void KinectWindow::on_btnAntigravityP2_clicked()
{
    p2Bonus = TypeSpecialBonusAntiGravity;
    validateBonus();
}

void KinectWindow::on_btnGuidedP2_clicked()
{
    p2Bonus = TypeSpecialBonusGuidedMissile;
    validateBonus();
}

void KinectWindow::on_btnTrackingP2_clicked()
{
    p2Bonus = TypeSpecialBonusTrackingMissile;
    validateBonus();
}

void KinectWindow::on_btnRootP2_clicked()
{
    p2Bonus = TypeSpecialBonusOmnidirectionalShot;
    validateBonus();
}

void KinectWindow::validateBonus()
{
    if(p1Bonus != TypeSpecialBonusNothing && p2Bonus != TypeSpecialBonusNothing)
    {
		menuMusic->stop();
        int duration = timer.hour() * 3600 + timer.minute() * 60 + timer.second();
        int difficulty = AlienMothership | Asteroids | Satellites | Supernovae | BlackSquadron;
        ge = new GameEngine(we, kinect, gameMode, duration, p1Ship, p2Ship, p1Bonus, p2Bonus, difficulty, this);
        connect(ge, SIGNAL(endGame()), this, SLOT(endGame()));
    }
}

void KinectWindow::endGame()
{
	ui->graphicsView->escapeGame();
	
    ge->deleteLater();
    ge = 0;

    ui->stack->setCurrentWidget(ui->home);
    p1Bonus = p2Bonus = TypeSpecialBonusNothing;
    p1Ship = p2Ship = NoSpaceShip;
	menuMusic->play();
}
