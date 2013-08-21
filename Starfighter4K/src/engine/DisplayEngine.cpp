#include "include/engine/DisplayEngine.h"
#include "include/engine/UserControlsEngine.h"
#include "include/engine/GameEngine.h"

#include "include/game/Displayable.h"
#include "include/game/Spaceship.h"
#include "include/game/BonusProjectile.h"
#include "include/game/BonusSpeed.h"

#include "include/utils/Settings.h"
#include "include/config/Define.h"

DisplayEngine::DisplayEngine(GameEngine *ge, QWidget *parent)
    :QWidget(parent),
      gameEngine(ge), isFullScreen(true), isTimer(false)
{
    // get screen dimension
    QDesktopWidget * desktop = QApplication::desktop();

    int screenSizeHeight = desktop->screenGeometry(this).height();
    int screenSizeWidth = desktop->screenGeometry(this).width();

    int sceneWidth = screenSizeWidth;
    int sceneHeigth = screenSizeHeight*0.90;

    QVBoxLayout * mainScreen = new QVBoxLayout(this);
    //QGridLayout * mainScreen = new QGridLayout(this);

    downHUD = new QWidget(this);

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
    view->move(0,0);

    mainScreen->setMargin(0);
    mainScreen->setSpacing(0);

    mainScreen->addWidget(view);
    mainScreen->addStretch();
    mainScreen->addWidget(downHUD);

    pixSpeed = QPixmap(ICON_BSPEED);
    pixProj = QPixmap(ICON_BATTACK);
    pixHP = QPixmap();

    explosionPicture = new QPixmap(screenSizeWidth,screenSizeHeight);
    explosionPicture->fill(Qt::transparent);

    QPainter painter(explosionPicture);
    painter.setBrush(QBrush(QColor(255,255,255,200)));
    painter.drawRect(0,0,screenSizeWidth,screenSizeHeight);

    splash = new QSplashScreen(*explosionPicture);

    affiche = new QTime();
    affiche->setHMS(0,0,0,0);

    setLayout(mainScreen);

    this->creatHUD();
}

DisplayEngine::~DisplayEngine()
{
    scene->clear();
    //Must clear the list in GameEngine

    delete bonusPlayerOne;
    delete bonusPlayerTwo;
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

void DisplayEngine::creatHUD()
{

    QHBoxLayout * downPart = new QHBoxLayout(downHUD);

    /**
      * Player no1 part
      */
    QHBoxLayout * playerOneNamu = new QHBoxLayout();
    //QGridLayout * playerOneNamu = new QGridLayout();
    //playerOneNamu->setColumnMinimumWidth(0,2);

    QLabel * player1Name = new QLabel(downHUD);
    //player1Name->setText("Name: player1");
    player1Name->setText(tr("Name : %1").arg(Settings::getGlobalSettings().playerOneName()));
    playerOneNamu->addWidget(player1Name);


    QGridLayout * statuePlayerOne = new QGridLayout();

    //QHBoxLayout * heathP1 = new QHBoxLayout();
   // QGridLayout * heathP1 = new QGridLayout();


    QLabel * lHP1 = new QLabel(tr("HP:\t"),downHUD);
    HP1= new QProgressBar(downHUD);
    HP1->setRange(0,100);
    HP1->setValue(100);


    QLabel * lShild1 = new QLabel(tr("Shield:\t"),downHUD);
    shield1= new QProgressBar(downHUD);
    shield1->setRange(0,100);
    shield1->setValue(100);

    // Add all layout status
    statuePlayerOne->addWidget(lHP1,0,0);
    statuePlayerOne->addWidget(HP1,0,1);
    statuePlayerOne->addWidget(lShild1,1,0);
    statuePlayerOne->addWidget(shield1,1,1);

    bonusPlayerOne = new QGridLayout();

    imSpeed1 = new QLabel(downHUD);
    imSpeed1->setPixmap(pixSpeed);
    imHP1 = new QLabel(downHUD);
    imHP1->setPixmap(pixHP);
    imProj1 = new QLabel(downHUD);
    imProj1->setPixmap(pixProj);

    lBSpeed1 = new QLabel(tr("1"),downHUD);
    lBHP1 = new QLabel(downHUD);
    lBProjectile1 = new QLabel(tr("Normal Shot"),downHUD);

    bonusPlayerOne->addWidget(imSpeed1,0,0,Qt::AlignHCenter);
    bonusPlayerOne->addWidget(lBSpeed1,1,0,Qt::AlignHCenter);

    bonusPlayerOne->addWidget(imHP1,0,3,Qt::AlignHCenter);
    bonusPlayerOne->addWidget(lBHP1,1,3,Qt::AlignHCenter);

    bonusPlayerOne->addWidget(imProj1,0,5,Qt::AlignHCenter);
    bonusPlayerOne->addWidget(lBProjectile1,1,5,Qt::AlignHCenter);

    QVBoxLayout * timeAndScore=0;
    if(gameEngine->getGameMode()==Timer)
    {
        /**
          * Timer and point counter
          */
        timeAndScore = new QVBoxLayout();
        QHBoxLayout * score = new QHBoxLayout();
        timer = new QLCDNumber(downHUD);
        timer->setDigitCount(5);

        scoreP1 = new QLCDNumber(downHUD);
        scoreP2 = new QLCDNumber(downHUD);

        scoreP1->setDigitCount(5);
        scoreP2->setDigitCount(5);
        score->addWidget(scoreP1);
        score->addWidget(new QLabel(tr(":"),downHUD));
        score->addWidget(scoreP2);

        timeAndScore->addWidget(timer);
        timeAndScore->addLayout(score);
    }

    /**
      * Player no2 part
      */
    QHBoxLayout * playerTwoNamu = new QHBoxLayout();
    QLabel * player2Name = new QLabel(downHUD);
    //player2Name->setText("Name: player2");
    player2Name->setText(tr("Name : %1").arg(Settings::getGlobalSettings().playerTwoName()));
    playerTwoNamu->addWidget(player2Name);

    QGridLayout * statuePlayerTwo = new QGridLayout();

    QHBoxLayout * heathP2 = new QHBoxLayout();
    QLabel * lHP2 = new QLabel(tr("HP:\t"),downHUD);
    HP2= new QProgressBar(downHUD);
    HP2->setRange(0,100);
    HP2->setValue(100);

    heathP2->addWidget(lHP2);
    heathP2->addWidget(HP2);

    //QHBoxLayout * shildP2 = new QHBoxLayout();
    QLabel * lShild2 = new QLabel(tr("Shield:\t"),downHUD);
    shield2= new QProgressBar(downHUD);
    shield2->setRange(0,100);
    shield2->setValue(100);

     // Add all layout status
    statuePlayerTwo->addWidget(lHP2,0,0);
    statuePlayerTwo->addWidget(HP2,0,1);
    statuePlayerTwo->addWidget(lShild2,1,0);
    statuePlayerTwo->addWidget(shield2,1,1);

    bonusPlayerTwo = new QGridLayout();

    imSpeed2 = new QLabel(downHUD);
    imSpeed2->setPixmap(pixSpeed);

    imHP2 = new QLabel(downHUD);
    imHP2->setPixmap(pixHP);

    imProj2 = new QLabel(downHUD);
    imProj2->setPixmap(pixProj);

    lBSpeed2 = new QLabel(tr("1"),downHUD);
    lBHP2 = new QLabel(downHUD);
    lBProjectile2 = new QLabel(tr("Normal Shot"),downHUD);

    bonusPlayerTwo->addWidget(imSpeed2,0,0,Qt::AlignHCenter);
    bonusPlayerTwo->addWidget(lBSpeed2,1,0,Qt::AlignHCenter);

    bonusPlayerTwo->addWidget(imHP2,0,3,Qt::AlignHCenter);
    bonusPlayerTwo->addWidget(lBHP2,1,3,Qt::AlignHCenter);

    bonusPlayerTwo->addWidget(imProj2,0,5,Qt::AlignHCenter);
    bonusPlayerTwo->addWidget(lBProjectile2,1,5,Qt::AlignHCenter);

    //QPixmap * icon2 = new QPixmap("./image/game/bonus");
    //bonusPlayerTwo->addWidget(icon2);

    downPart->addLayout(playerOneNamu);
    downPart->addSpacing(SPACE_INPLAYER);
    downPart->addLayout(statuePlayerOne);
    downPart->addSpacing(SPACE_INPLAYER);
    downPart->addLayout(bonusPlayerOne);
    downPart->addSpacing(SPACE_BETWEEN);
    if(gameEngine->getGameMode()==Timer)
        downPart->addLayout(timeAndScore);
    downPart->addSpacing(SPACE_BETWEEN);
    downPart->addLayout(playerTwoNamu);
    downPart->addSpacing(SPACE_INPLAYER);
    downPart->addLayout(statuePlayerTwo);
    downPart->addSpacing(SPACE_INPLAYER);
    downPart->addLayout(bonusPlayerTwo);

    //scene->setSceneRect(0,0,screenSizeWidth,screenSizeHeight);
    //downHUD->move(0,screenSizeHeight-125);
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
    HP1->setValue(_value);
}

void DisplayEngine::setProgressHP2(int _value)
{
    HP2->setValue(_value);
}

void DisplayEngine::setProgressShield1(int _value)
{
    shield1->setValue(_value);
}

void DisplayEngine::setProgressShield2(int _value)
{
    shield2->setValue(_value);
}

void DisplayEngine::setGameScore1(int _value)
{
    scoreP1->display(_value);
}

void DisplayEngine::setGameScore2(int _value)
{
    scoreP2->display(_value);
}

void DisplayEngine::setBonusProject1(TypeProjectiles _value)
{

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
}

void DisplayEngine::setBonusProject2(TypeProjectiles _value)
{

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
}

void DisplayEngine::setBonusSpeed1(int _value)
{
    if(_value != 1)
        lBSpeed1->setText(QString("%1%").arg(_value));
    else
        lBSpeed1->setNum(1);
}

void DisplayEngine::setBonusSpeed2(int _value)
{
    if(_value != 1)
        lBSpeed2->setText(QString("%1%").arg(_value));
    else
        lBSpeed2->setNum(1);
}


void DisplayEngine::updateGameData()
{
    this->setProgressHP1(gameEngine->ship1()->getHealthPoint());
    this->setProgressHP2(gameEngine->ship2()->getHealthPoint());

    this->setProgressShield1(gameEngine->ship1()->getHealthForceField());
    this->setProgressShield2(gameEngine->ship2()->getHealthForceField());

    BonusProjectile * getBonus = gameEngine->ship1()->getBonusProjectile();
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
    this->setBonusSpeed2(gameEngine->ship2()->getPercentageSpeed());


    if(gameEngine->getHasSomeonWon())
    {
        gameEngine->userControlsEngine()->clearActionList();
    }
}

void DisplayEngine::updateGameDataTimer(int s)
{
    affiche->setHMS(0,s/60,s%60);

    timer->display(affiche->toString("mm:ss"));
    scoreP1->display(gameEngine->ship1()->getScore());
    scoreP2->display(gameEngine->ship2()->getScore());

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
        gameEngine->userControlsEngine()->keyPressEvent(event);
        break;
    }

}


void DisplayEngine::keyReleaseEvent(QKeyEvent * event)
{
    gameEngine->userControlsEngine()->keyReleaseEvent(event);
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
