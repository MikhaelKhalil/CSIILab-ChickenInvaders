#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"
#include <QGraphicsRectItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player *player;
    Enemy(Player *p);

public slots:
    void move();
};

#endif // ENEMY_H
