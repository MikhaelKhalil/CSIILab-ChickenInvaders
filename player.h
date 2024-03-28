#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QObject>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

private:
    int score;
    int health;
    QGraphicsTextItem *scoreText;
    QGraphicsTextItem *healthText;
    QAudioOutput *bulletSoundOutput;
    QMediaPlayer *bulletSound;
    QAudioOutput *scoreSound1Output;
    QMediaPlayer *scoreSound1;
    QAudioOutput *scoreSound2Output;
    QMediaPlayer *scoreSound2;
    QAudioOutput *healthSoundOutput;
    QMediaPlayer *healthSound;

public:
    Player(QGraphicsTextItem *s, QGraphicsTextItem *h);

    // Getters
    int getScore();
    int getHealth();

    // Setters
    void increaseScore();
    void decreaseHealth();

public:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void createEnemy();
};

#endif // PLAYER_H
