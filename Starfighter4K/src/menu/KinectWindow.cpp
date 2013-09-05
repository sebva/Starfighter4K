#include "include/menu/KinectWindow.h"
#include "ui_KinectWindow.h"
#include "include/engine/GameEngine.h"
#include "include/engine/WiimoteEngine.h"
#include "include/engine/GameEngine.h"
#include "include/kinect/qkinect.h"
#include "include/utils/Settings.h"
#include "include/config/Define.h"

KinectWindow::KinectWindow(WiimoteEngine *we, QKinect* kinect, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::KinectWindow),
	p1Ship(NoSpaceShip), p2Ship(NoSpaceShip),
	p1Bonus(TypeSpecialBonusNothing), p2Bonus(TypeSpecialBonusNothing),
	we(we), kinect(kinect), ge(0),
	background(":/images/menu/background"),
	kinectActive(true)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	setPalette(Qt::transparent);
	setAttribute(Qt::WA_DeleteOnClose);

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

	hoverButtons = new BlurPushButton*[2];
	hoverButtons[0] = hoverButtons[1] = 0;

	connect(ui->btnAntigravityP1, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnFreezeP1, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnGuidedP1, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnRootP1, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnTrackingP1, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);

	connect(ui->btnAntigravityP2, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnFreezeP2, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnGuidedP2, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnRootP2, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);
	connect(ui->btnTrackingP2, &BlurPushButton::clicked, this, &KinectWindow::validateBonus);

	connect(ui->btnShip1P1, &BlurPushButton::clicked, this, &KinectWindow::validateShips);
	connect(ui->btnShip2P1, &BlurPushButton::clicked, this, &KinectWindow::validateShips);
	connect(ui->btnShip3P1, &BlurPushButton::clicked, this, &KinectWindow::validateShips);

	connect(ui->btnShip1P2, &BlurPushButton::clicked, this, &KinectWindow::validateShips);
	connect(ui->btnShip2P2, &BlurPushButton::clicked, this, &KinectWindow::validateShips);
	connect(ui->btnShip3P2, &BlurPushButton::clicked, this, &KinectWindow::validateShips);

	p1BonusGroup.addButton(ui->btnAntigravityP1, TypeSpecialBonusAntiGravity);
	p1BonusGroup.addButton(ui->btnFreezeP1, TypeSpecialBonusFreeze);
	p1BonusGroup.addButton(ui->btnGuidedP1, TypeSpecialBonusGuidedMissile);
	p1BonusGroup.addButton(ui->btnRootP1, TypeSpecialBonusOmnidirectionalShot);
	p1BonusGroup.addButton(ui->btnTrackingP1, TypeSpecialBonusTrackingMissile);

	p2BonusGroup.addButton(ui->btnAntigravityP2, TypeSpecialBonusAntiGravity);
	p2BonusGroup.addButton(ui->btnFreezeP2, TypeSpecialBonusFreeze);
	p2BonusGroup.addButton(ui->btnGuidedP2, TypeSpecialBonusGuidedMissile);
	p2BonusGroup.addButton(ui->btnRootP2, TypeSpecialBonusOmnidirectionalShot);
	p2BonusGroup.addButton(ui->btnTrackingP2, TypeSpecialBonusTrackingMissile);

	p1ShipsGroup.addButton(ui->btnShip1P1, SpaceshipType1);
	p1ShipsGroup.addButton(ui->btnShip2P1, SpaceshipType2);
	p1ShipsGroup.addButton(ui->btnShip3P1, SpaceshipType3);

	p2ShipsGroup.addButton(ui->btnShip1P2, SpaceshipType1);
	p2ShipsGroup.addButton(ui->btnShip2P2, SpaceshipType2);
	p2ShipsGroup.addButton(ui->btnShip3P2, SpaceshipType3);
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
	QMainWindow::paintEvent(event);

	QPainter p(this);
	p.drawPixmap(0, 0, background);
}

void KinectWindow::handsMoved()
{
	if(!kinectActive)
		return;

	QPair<QPoint, QPoint> hands = kinect->getHandsPosition();
	hand1 = hands.first;
	hand2 = hands.second;

	BlurPushButton* button1;
	if(button1 = dynamic_cast<BlurPushButton*>(childAt(hand1)))
	{
		if(hoverButtons[0] != 0 && hoverButtons[0] != button1)
			hoverButtons[0]->setHandOnTop(false);
		button1->setHandOnTop(true);
		hoverButtons[0] = button1;
	}
	else if(hoverButtons[0] != 0)
		hoverButtons[0]->setHandOnTop(false);
	BlurPushButton* button2;
	if(button2 = dynamic_cast<BlurPushButton*>(childAt(hand2)))
	{
		if(hoverButtons[1] != 0 && hoverButtons[1] != button2)
			hoverButtons[1]->setHandOnTop(false);
		button2->setHandOnTop(true);
		hoverButtons[1] = button2;
	}
	else if(hoverButtons[1] != 0)
		hoverButtons[1]->setHandOnTop(false);
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

	ui->stack->setCurrentWidget(ui->options);
}

void KinectWindow::on_btnValidateOptions_clicked()
{
	Settings& s = Settings::getGlobalSettings();

	s.setPlayerOneName(ui->p1name->text());
	s.setPlayerTwoName(ui->p2name->text());

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

	unselectBonuses();
	unselectShips();

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

void KinectWindow::unselectShips()
{
	p1ShipsGroup.setExclusive(false);
	p2ShipsGroup.setExclusive(false);
	ui->btnShip1P1->setChecked(false);
	ui->btnShip2P1->setChecked(false);
	ui->btnShip3P1->setChecked(false);
	ui->btnShip1P2->setChecked(false);
	ui->btnShip2P2->setChecked(false);
	ui->btnShip3P2->setChecked(false);
	p1ShipsGroup.setExclusive(true);
	p2ShipsGroup.setExclusive(true);
}

void KinectWindow::unselectBonuses()
{
	p1BonusGroup.setExclusive(false);
	p2BonusGroup.setExclusive(false);
	ui->btnAntigravityP1->setChecked(false);
	ui->btnFreezeP1->setChecked(false);
	ui->btnGuidedP1->setChecked(false);
	ui->btnRootP1->setChecked(false);
	ui->btnTrackingP1->setChecked(false);
	ui->btnAntigravityP2->setChecked(false);
	ui->btnFreezeP2->setChecked(false);
	ui->btnGuidedP2->setChecked(false);
	ui->btnRootP2->setChecked(false);
	ui->btnTrackingP2->setChecked(false);
	p1BonusGroup.setExclusive(true);
	p2BonusGroup.setExclusive(true);
}

void KinectWindow::validateShips(int)
{
	int p1ShipId = p1ShipsGroup.checkedId();
	int p2ShipId = p2ShipsGroup.checkedId();
	if(p1ShipId != -1 && p2ShipId != -1)
	{
		p1Ship = (SpaceshipType)p1ShipId;
		p2Ship = (SpaceshipType)p2ShipId;
		ui->stack->setCurrentWidget(ui->bonusSelection);
	}
}

void KinectWindow::validateBonus(int)
{
	int p1BonusId = p1BonusGroup.checkedId();
	int p2BonusId = p2BonusGroup.checkedId();
	if(p1BonusId != -1 && p2BonusId != -1)
	{
		p1Bonus = (TypeSpecialBonus)p1BonusId;
		p2Bonus = (TypeSpecialBonus)p2BonusId;

		kinectActive = false;

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

	unselectBonuses();
	unselectShips();

	ui->stack->setCurrentWidget(ui->home);
	p1Bonus = p2Bonus = TypeSpecialBonusNothing;
	p1Ship = p2Ship = NoSpaceShip;
	menuMusic->play();

	kinectActive = true;
}
