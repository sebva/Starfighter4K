#ifndef DEMOENGINE_H
#define DEMOENGINE_H

#include "GameEngine.h"
#include <QtWidgets>

class QGraphicsScene;
class QGraphicsView;

class DemoEngine : public GameEngine
{
    Q_OBJECT

public:
    DemoEngine(QWidget * = 0);
    ~DemoEngine(){}

    qreal xminWarzone() const;
    qreal xmaxWarZone() const;
    QRect sceneSize() const;

    void addProjectile(Projectile *_inProjectile);
    void addSmallAsteroid(Asteroid *_inAsteroide);
    void addBonus(Bonus *_inBonus);
    void addAlienSpaceship(AlienSpaceship *_inAlienSpaceship);
    void addAsteroid(Asteroid *_inAsteroide);

public slots:
    void elemenDestroyed(Destroyable* _destroyItem, int nbPoint, Shooter forShip);

private:
    void resizeEvent(QResizeEvent *event);
    void timerEvent(QTimerEvent *);

    const static int offset = 10;

    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* bgScene;
    QPixmap bg;
    qreal angleBg;
};

#endif // DEMOENGINE_H
