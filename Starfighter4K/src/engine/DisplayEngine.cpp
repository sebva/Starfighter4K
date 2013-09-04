#include "include/engine/DisplayEngine.h"
#include "include/engine/UserControlsEngine.h"
#include "include/engine/GameEngine.h"
#include "include/engine/SpawnEngine.h"

#include "include/game/Displayable.h"
#include "include/game/Spaceship.h"
#include "include/game/BonusProjectile.h"
#include "include/game/BonusInvicibility.h"

#include "include/utils/Settings.h"
#include "include/config/Define.h"
#include "include/menu/HUDWidget.h"
#include "include/config/define.h"

DisplayEngine::DisplayEngine(GameEngine *ge, QWidget *parent)
    :QMainWindow(parent),
      gameEngine(ge), isFullScreen(true),angleBg(M_PI/4.0),bg(BACKGROUND),countDown(NB_COUNTDOWN),tCountDown(new QTimer),message(0)
{
    // get screen dimension
    QDesktopWidget * desktop = QApplication::desktop();

    int screenSizeHeight = desktop->screenGeometry(this).height();
    int screenSizeWidth = desktop->screenGeometry(this).width();

    //QVBoxLayout * mainScreen = new QVBoxLayout(this);
    //QGridLayout * mainScreen = new QGridLayout(this);

    hud = new HUDWidget(gameEngine, this);
    hud->setPlayerName(Player1, Settings::getGlobalSettings().playerOneName());
    hud->setPlayerName(Player2, Settings::getGlobalSettings().playerTwoName());
    this->addDockWidget(Settings::getGlobalSettings().HUDArea(), hud);

    int sceneWidth = screenSizeWidth;
    int sceneHeigth = screenSizeHeight - hud->height();

    // configuration of QGraphicsScene and QGraphicsview
    scene = new QGraphicsScene(0,0,sceneWidth,sceneHeigth,this);
    view = new QGraphicsView(scene,this);

    view->setFixedSize(sceneWidth,sceneHeigth);

    view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view->setViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer),this));
    view->setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing|QPainter::TextAntialiasing);

    //Better performance if we don't use random access in the scene.
    //It's the case because we use QList for Item process
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view->viewport()->setFocusProxy( this );
    view->setFocusPolicy(Qt::NoFocus);

    // Set background

    bgScene = scene->addPixmap(bg);
    //bg = bg.scaled(sceneWidth, sceneHeigth, Qt::KeepAspectRatioByExpanding);

    //scene->setBackgroundBrush(Qt::black);
    this->setFixedSize(screenSizeWidth,screenSizeHeight);

    this->setWindowModality(Qt::ApplicationModal);
    // Param of the screen
    //showFullScreen();
    switchFullScreen();
    //setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);

    setCentralWidget(view);

    explosionPicture = new QPixmap(screenSizeWidth,screenSizeHeight);
    explosionPicture->fill(Qt::transparent);

    QPainter painter(explosionPicture);
    painter.setBrush(QBrush(QColor(255,255,255,200)));
    painter.drawRect(0,0,screenSizeWidth,screenSizeHeight);

    splash = new QSplashScreen(*explosionPicture);

    affiche = new QTime();
    affiche->setHMS(0,0,0,0);
    bgScene->setPos(-(offset+1),-(offset+1));

	QFontDatabase().addApplicationFont(FONT_PATH);
}

void DisplayEngine::startCountDown()
{
	text = new QGraphicsTextItem(QString("%1").arg(countDown));
	text->setFont(QFont("Helvetica Neue", 72, QFont::Light));
	text->setDefaultTextColor(QColor(Qt::white));
	text->setPos(scene->width()/2.0-text->document()->documentLayout()->documentSize().width()/2.0,
		scene->height()/2.0-text->document()->documentLayout()->documentSize().height()/2.0);
	tCountDown->start(17);
	connect(tCountDown,SIGNAL(timeout()),this,SLOT(changeCountDown()));
	scene->addItem(text);
}

void DisplayEngine::changeCountDown()
{
	if(text->opacity()<=0.05)
	{
		if(--countDown >= 0)
		{
			text->setOpacity(1.0);
			if(countDown == 0)
			{
				text->setPlainText(QString("FIGHT !"));
				text->setFont(QFont("Helvetica Neue", 48, QFont::Light));
				text->setPos(scene->width()/2.0-text->document()->documentLayout()->documentSize().width()/2.0,
					scene->height()/2.0-text->document()->documentLayout()->documentSize().height()/2.0);
			}
			else
				text->setPlainText(QString("%1").arg(countDown));
		}
		else
		{
			gameEngine->start();
			hud->startTimer();
			delete text;
			delete tCountDown;
		}
	}
	else
		text->setOpacity(0.92*text->opacity());
}

void DisplayEngine::moveBG()
{
    int factorX = (cos(angleBg) >= 0) ? -1 : 1;
    int factorY = (sin(angleBg) >= 0) ? -1 : 1;//Inverse

    if(bgScene->pos().y()+bg.height() <= sceneSize().height()+offset
            || bgScene->pos().x()+bg.width() <= sceneSize().width()+offset
            || bgScene->pos().y()+offset >= 0
            || bgScene->pos().x()+offset >= 0)
    {
        angleBg -= M_PI/2.0;
        factorX = (cos(angleBg) >= 0) ? -1 : 1;
        factorY = (sin(angleBg) >= 0) ? -1 : 1;//Inverse
    }

    bgScene->moveBy(factorX*BACKGROUND_DX,factorY*BACKGROUND_DY);
}

DisplayEngine::~DisplayEngine()
{
    scene->clear();
	qDeleteAll(scene->items());
    //Must clear the list in GameEngine

    delete affiche;
    delete explosionPicture;
    delete splash;
    //All Layout,QLabel,QLCDNumber,QProgressbar delete with parent of QWidget

    //GameEnfine call ~DisplayEngine
}

void DisplayEngine::explosionScreen()
{
    splash->showFullScreen();
    splash->raise();

    QTimer::singleShot(300,this,SLOT(removeExplosionScreen()));
}

void DisplayEngine::removeExplosionScreen()
{
    splash->finish(this);
}

QRect DisplayEngine::sceneSize() const
{
    return QRect(0,0,scene->width(),scene->height());
}

qreal DisplayEngine::xminWarzone() const
{
    return gameEngine->ship1()->sizePixmap().width()*2;
}

qreal DisplayEngine::xmaxWarZone() const
{
    return scene->width()-2*(gameEngine->ship2()->sizePixmap().width());
}

void DisplayEngine::addItemScene(Displayable* item)
{
    scene->addItem(item);
}

void DisplayEngine::removeItemScene(Displayable *item)
{
    scene->removeItem(item);
}

void DisplayEngine::updateScreen()
{
    scene->advance();
}

void DisplayEngine::setProgressHP1(int _value)
{
    hud->setPlayerHP(Player1, _value);
}

void DisplayEngine::setProgressHP2(int _value)
{
    hud->setPlayerHP(Player2, _value);
}

void DisplayEngine::setProgressShield1(int _value)
{
    hud->setPlayerShield(Player1, _value);
}

void DisplayEngine::setProgressShield2(int _value)
{
    hud->setPlayerShield(Player2, _value);
}

void DisplayEngine::setGameScore1(int _value)
{
    hud->setPlayerScore(Player1, _value);
}

void DisplayEngine::setGameScore2(int _value)
{
    hud->setPlayerScore(Player2, _value);
}

void DisplayEngine::updateGameData()
{
    this->setProgressHP1(gameEngine->ship1()->getHealthPoint());
    this->setProgressHP2(gameEngine->ship2()->getHealthPoint());

    this->setProgressShield1(gameEngine->ship1()->getHealthForceField());
    this->setProgressShield2(gameEngine->ship2()->getHealthForceField());

    if(gameEngine->getHasSomeonWon())
    {
        gameEngine->userControlsEngine()->clearActionList();
    }
}

void DisplayEngine::updateGameDataTimer(int s)
{
    affiche->setHMS(0,s/60,s%60);

    hud->setTimer(*affiche);
    setGameScore1(gameEngine->ship1()->getScore());
    setGameScore2(gameEngine->ship2()->getScore());

}


void DisplayEngine::keyPressEvent(QKeyEvent *event)
{

    switch(event->key())
    {
        case Qt::Key_F12:
        this->switchFullScreen();
        break;

        case Qt::Key_Escape:
        gameEngine->escapeGame(true);
        break;

        default:
        break;
    }

}

void DisplayEngine::closeEvent(QCloseEvent *event)
{
    gameEngine->escapeGame();
    event->ignore();
}


void DisplayEngine::switchFullScreen()
{
    if(isFullScreen)
        // Param of the screen
        showFullScreen();
    else
        showMaximized();

    isFullScreen = !isFullScreen;
}

void DisplayEngine::showMessage(const QString& str)
{
	message = new QGraphicsTextItem(str);
	message->setZValue(10000);
	message->setFont(QFont("Helvetica Neue", 48, QFont::Light));
	message->setDefaultTextColor(QColor(Qt::white));
	message->setPos(scene->width()/2.0-message->document()->documentLayout()->documentSize().width()/2.0,
		scene->height()/2.0-message->document()->documentLayout()->documentSize().height()/2.0);
	scene->addItem(message);
}

void DisplayEngine::removeMessage()
{
	if(message != 0)
	{
		delete message;
		message = 0;
	}
}