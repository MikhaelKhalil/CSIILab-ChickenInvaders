#ifndef BULLET_H
#define BULLET_H
#include "player.h"
#include <QGraphicsItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT
public:
    Player *player;

    Bullet(Player *p);

public slots:
    void move();
};

#endif // BULLET_H
