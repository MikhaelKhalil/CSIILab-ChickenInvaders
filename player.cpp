#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <stdlib.h> // rand() -> to determine which score sound effect will be played

Player::Player() {

}

void Player::keyPressEvent(QKeyEvent *event) {
    // *******  Event Handling for the Player ********
    if (event->key() == Qt::Key_Left) {
        if (x() > 0) // to prevent the player from getting out of the screen
        {
            setPos(x() - 10, y());
        }
    } else if (event->key() == Qt::Key_Right) {
        if (x() + 100 < 800) // to prevent the player from getting out of the screen
            setPos(x() + 10, y());
    } else if (event->key() == Qt::Key_Space) {
        Bullet *bullet = new Bullet(this);
        bullet->setPos(x() + 10, y() - 35);
        scene()->addItem(bullet);
    }
}

// CreateEnemy function used to create the eneimes
void Player::createEnemy() {
    Enemy *enemy = new Enemy(this);
    scene()->addItem(enemy);
}
