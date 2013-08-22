#include "include/engine/DisplayEngine.h"
#include "include/engine/UserControlsEngine.h"
#include "include/engine/GameEngine.h"

#include "include/game/Displayable.h"
#include "include/game/Spaceship.h"
#include "include/game/BonusProjectile.h"
#include "include/game/BonusInvicibility.h"

#include "include/utils/Settings.h"
#include "include/config/Define.h"
#include "include/menu/HUDWidget.h"

DisplayEngine::DisplayEngine(GameEngine *ge, QWidget *parent)
    :QMainWindow(parent),
      gameEngine(ge), isFullScreen(true)
{
    // get screen dimension
    QDesktopWidget * desktop = QApplication::desktop();

    int screenSizeHeight = desktop->screenGeometry(this).height();
    int screenSizeWidth = desktop->screenGeometry(this).width();

    //QVBoxLayout * mainScreen = new QVBoxLayout(this);
    //QGridLayout * mainScreen = new QGridLayout(this);

    hud = new HUDWidget(this, gameEngine->getGameMode());
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

    //Better performance if we don't use random access in the scene.
    //It's the case because we use QList for Item process
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view->viewport()->setFocusProxy( this );
    view->setFocusPolicy(Qt::NoFocus);

    // Set background
    QPixmap bg( BACKGROUND );
    bg = bg.scaled(sceneWidth, sceneHeigth, Qt::KeepAspectRatioByExpanding);

    scene->setBackgroundBrush(bg);
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
}

DisplayEngine::~DisplayEngine()
{
    scene->clear();
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

void DisplayEngine::setBonusProject1(TypeProjectiles _value)
{

    /* TODO
    switch(_value)
    {
        case ProjSimple:
            imProj1->setText("");
            lBProjectile1->setText(tr("Standard Shot"));
        break;

        case ProjCross:
            imProj1->setPixmap(pixProj);
            lBProjectile1->setText(tr("Cross Shot"));
        break;

        case ProjV:
            imProj1->setPixmap(pixProj);
            lBProjectile1->setText(tr("V Shot"));
        break;

        case ProjAlien:
        break;

        case Nothing:
        break;
    }
    */
}

void DisplayEngine::setBonusProject2(TypeProjectiles _value)
{
    /* TODO
    switch(_value)
    {
        case ProjSimple:
            imProj2->setText("");
            lBProjectile2->setText(tr("Standard Shot"));
        break;

        case ProjCross:
            imProj2->setPixmap(pixProj);
            lBProjectile2->setText(tr("Cross Shot"));
        break;

        case ProjV:
        imProj2->setPixmap(pixProj);
        lBProjectile2->setText(tr("V Shot"));
        break;

        case ProjAlien:
        break;

        case Nothing:
        break;
    }
    */
}

void DisplayEngine::updateGameData()
{
    this->setProgressHP1(gameEngine->ship1()->getHealthPoint());
    this->setProgressHP2(gameEngine->ship2()->getHealthPoint());

    this->setProgressShield1(gameEngine->ship1()->getHealthForceField());
    this->setProgressShield2(gameEngine->ship2()->getHealthForceField());

    /*BonusProjectile * getBonus = gameEngine->ship1()->getBonusProjectile();
    if(getBonus != NULL)
        this->setBonusProject1(getBonus->getType());
    else
        this->setBonusProject1();

    getBonus = gameEngine->ship2()->getBonusProjectile();
    if(getBonus != NULL)
        this->setBonusProject2(getBonus->getType());
    else
        this->setBonusProject2();

    this->setBonusSpeed1(gameEngine->ship1()->getPercentageSpeed());
    this->setBonusSpeed2(gameEngine->ship2()->getPercentageSpeed());*/


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
        gameEngine->escapeGame();
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
