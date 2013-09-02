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

    void addBlackship(Blackship* _blackship);
    void addProjectile(Projectile *_inProjectile);
    void addSmallAsteroid(Asteroid *_inAsteroide);
    void addBonus(Bonus *_inBonus);
    void addAlienSpaceship(AlienSpaceship *_inAlienSpaceship);
    void addAsteroid(Asteroid *_inAsteroide);
    void removeItemScene(Displayable* item);

	void escapeGame();

public slots:
    void elemenDestroyed(Destroyable* _destroyItem, int nbPoint, Shooter forShip);

private:
    void resizeEvent(QResizeEvent *);
    void timerEvent(QTimerEvent *);

	int idTimer;
    const static int offset = 10;

    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* bgScene;
    QPixmap bg;
    qreal angleBg;
};

#endif // DEMOENGINE_H
