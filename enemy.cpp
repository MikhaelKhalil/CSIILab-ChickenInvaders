#include "enemy.h"
#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <stdlib.h> // rand() -> to generate really large integer

Enemy::Enemy(Player *p) {
    player = p;

    // *******  Setting the size of the enemy ********
    setPixmap(QPixmap(":/assets/assets/imgs/chicken.png").scaled(60, 60));

    // *******  Setting the postion of the enemy within the view dimensions
    // ********
    int random_number = rand() % 700;
    setPos(random_number, 0);

    // *******  Moving the enemies downwards automatically every 50 milli second
    // ********
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

// Function move: move the enemy downwards untill the end of the scene then
// remove it and delete it
void Enemy::move() {
    setPos(x(), y() + 5);
    if (y() + 60 >
        800) { // 50 is the height of chicken.png. It's hard-coded here.
        scene()->removeItem(this);
        delete this;
    }

    QList<QGraphicsItem *> collidingItemsList2 = collidingItems();
    for (int i = 0; i < collidingItemsList2.size(); i++) {
        if (typeid(*collidingItemsList2[i]) == typeid(Player)) {
            scene()->removeItem(this);
            delete this;
            player->decreaseHealth();
            return;
        }
    }
}
