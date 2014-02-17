#include "include/engine/DemoEngine.h"
#include "include/config/Define.h"
#include "include/game/Asteroid.h"
#include "include/game/AlienSpaceship.h"
#include "include/game/Bonus.h"
#include "include/game/Asteroid.h"
#include "include/game/BlackShip.h"
#include "include/engine/SpawnEngine.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <include/stable.h>
DemoEngine::DemoEngine(QWidget* parent):GameEngine(parent),bg(BACKGROUND),angleBg(M_PI/4.0)
{
    scene = new QGraphicsScene(0,0,width(),height(),this);
    setScene(scene);

    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer),this));
    setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing);

    //Better performance if we don't use random access in the scene.
    //It's the case because we use QList for Item process
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    viewport()->setFocusProxy( this );
    setFocusPolicy(Qt::NoFocus);
    bgScene = scene->addPixmap(bg);
    bgScene->setPos(-(offset+1),-(offset+1));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //show();
    idTimer = startTimer(REFRESH);
	se->start();
}

DemoEngine::~DemoEngine()
{
	delete bgScene;
	qDeleteAll(scene->items());
}

void DemoEngine::resizeEvent(QResizeEvent *)
{
    setSceneRect(QRect(QPoint(0, 0), size()));
    scene->setSceneRect(QRect(QPoint(0, 0), size()));
    fitInView(QRect(QPoint(0, 0), size()));
}

void DemoEngine::escapeGame(bool isKey)
{
	if(idTimer == -1)
	{
		idTimer = startTimer(REFRESH);
		emit signalPause(false);
	}
	else
	{
		killTimer(idTimer);
		idTimer = -1;
		emit signalPause(true);
	}
}

void DemoEngine::timerEvent(QTimerEvent *)
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

    scene->advance();

    checkOutsideScene(listProjectile);
    checkOutsideScene(listAsteroide);
    checkOutsideScene(listSmallAsteroide);
    checkOutsideScene(listBonus);
    checkOutsideScene(listAlienSpaceship);

    runTestCollision(listProjectile);
    clearList(listProjectile);

    runTestCollision(listAsteroide);
    runTestCollision(listSmallAsteroide);
}

qreal DemoEngine::xminWarzone() const
{
    return 0;
}

qreal DemoEngine::xmaxWarZone() const
{
    return scene->width();
}

QRect DemoEngine::sceneSize() const
{
    return QRect(0,0,scene->width(),scene->height());
}

void DemoEngine::addAsteroid(Asteroid *_inAsteroid)
{
    scene->addItem(_inAsteroid);
    listAsteroide.append(_inAsteroid);
    connect(_inAsteroid,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void DemoEngine::addBlackship(Blackship* _blackship)
{
    scene->addItem(_blackship);
    listBlackship.append(_blackship);
    connect(_blackship,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void DemoEngine::addProjectile(Projectile *_inProjectile)
{
    scene->addItem(_inProjectile);
	listProjectile.append(_inProjectile);
}

void DemoEngine::addSmallAsteroid(Asteroid *_inAsteroid)
{
    scene->addItem(_inAsteroid);
    listSmallAsteroide.append(_inAsteroid);
    connect(_inAsteroid,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void DemoEngine::addBonus(Bonus *_inBonus)
{
    scene->addItem(_inBonus);
    listBonus.append(_inBonus);
}

void DemoEngine::addAlienSpaceship(AlienSpaceship *_inAlienSpaceship)
{
    scene->addItem(_inAlienSpaceship);
    listAlienSpaceship.append(_inAlienSpaceship);
    connect(_inAlienSpaceship,SIGNAL(destroyed(Destroyable*,int,Shooter)),this,SLOT(elemenDestroyed(Destroyable*,int,Shooter)));
}

void DemoEngine::elemenDestroyed(Destroyable *_destroyItem, int, Shooter)
{
    if(Asteroid* a = dynamic_cast<Asteroid*>(_destroyItem))
    {
        if(a->isSmall())
            removeSmallAsteroid(a);
        else
            removeAsteroid(a);
    }
    else if(AlienSpaceship* a = dynamic_cast<AlienSpaceship*>(_destroyItem))
        removeAlienSpaceship(a);
}

void DemoEngine::removeItemScene(Displayable* item)
{
    scene->removeItem(item);
}
