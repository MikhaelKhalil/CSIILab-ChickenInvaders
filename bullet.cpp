#include "bullet.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <enemy.h>
#include <player.h>

Bullet::Bullet(Player *p) : QObject(), QGraphicsPixmapItem() {
    player = p;

    // *******  Setting the bullets' size ********
    setPixmap(QPixmap(":/assets/assets/imgs/laser.png").scaled(20, 40));

    // *******  Generating the Bullets automatically ********
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

// Move function is used to 1-  move the bullet upwards
// 2- Handle the collision of the bullets with enemies
void Bullet::move() {
    // *******  Getting the colliding items with the Bullet ********
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (int i = 0; i < collidingItemsList.size(); i++) {
        if (typeid(*collidingItemsList[i]) == typeid(Enemy)) {
            scene()->removeItem(collidingItemsList[i]);
            scene()->removeItem(this);
            delete collidingItemsList[i];
            delete this;
            player->increaseScore();
            return;
        }
    }

    // *******  Moving the bullets upward ********
    setPos(x(), y() - 10);
    if (y() + 40 < 0) { // 50 is the height of laser.png. It's hard-coded here.
        scene()->removeItem(this);
        delete this;
    }
}
