#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <QApplication> // quit() -> to quit the game after game is over
#include <QAudioOutput>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMessageBox>
#include <stdlib.h> // rand() -> to determine which score sound effect will be played

Player::Player(QGraphicsTextItem *s, QGraphicsTextItem *h) {
    score = 0;
    health = 3;
    scoreText = s;
    healthText = h;

    QAudioOutput *bulletSoundOutput = new QAudioOutput;
    bulletSoundOutput->setVolume(100);
    bulletSound = new QMediaPlayer;
    bulletSound->setAudioOutput(bulletSoundOutput);
    bulletSound->setSource(QUrl("qrc:/assets/assets/audio/bullet.wav"));

    QAudioOutput *scoreSound1Output = new QAudioOutput;
    scoreSound1Output->setVolume(100);
    scoreSound1 = new QMediaPlayer;
    scoreSound1->setAudioOutput(scoreSound1Output);
    scoreSound1->setSource(QUrl("qrc:/assets/assets/audio/kill1.mp3"));

    QAudioOutput *scoreSound2Output = new QAudioOutput;
    scoreSound2Output->setVolume(100);
    scoreSound2 = new QMediaPlayer;
    scoreSound2->setAudioOutput(scoreSound2Output);
    scoreSound2->setSource(QUrl("qrc:/assets/assets/audio/kill2.mp3"));

    QAudioOutput *healthSoundOutput = new QAudioOutput;
    healthSoundOutput->setVolume(100);
    healthSound = new QMediaPlayer;
    healthSound->setAudioOutput(healthSoundOutput);
    healthSound->setSource(QUrl("qrc:/assets/assets/audio/damage.wav"));
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

        if (bulletSound->playbackState() == QMediaPlayer::PlayingState) {
            bulletSound->setPosition(0);
        } else if (bulletSound->playbackState() == QMediaPlayer::StoppedState) {
            bulletSound->play();
        }
    }
}

// CreateEnemy function used to create the eneimes
void Player::createEnemy() {
    Enemy *enemy = new Enemy(this);
    scene()->addItem(enemy);
}

// Getters
int Player::getScore() { return score; }
int Player::getHealth() { return health; }

// Setters
void Player::increaseScore() {
    score++;
    scoreText->setPlainText("Score: " + QString::number(score));

    QMediaPlayer *scoreSound;
    int randomSoundEffect = rand() % 2;
    if (randomSoundEffect == 0) {
        scoreSound = scoreSound1;
    } else {
        scoreSound = scoreSound2;
    }

    if (scoreSound->playbackState() == QMediaPlayer::PlayingState) {
        scoreSound->setPosition(0);
    } else if (scoreSound->playbackState() == QMediaPlayer::StoppedState) {
        scoreSound->play();
    }
}
void Player::decreaseHealth() {
    health--;
    healthText->setPlainText("Health: " + QString::number(health));

    if (healthSound->playbackState() == QMediaPlayer::PlayingState) {
        healthSound->setPosition(0);
    } else if (healthSound->playbackState() == QMediaPlayer::StoppedState) {
        healthSound->play();
    }

    if (health < 1) {
        QMessageBox *msg = new QMessageBox;
        msg->setText("Game Over! Your scored " + QString::number(score) +
                     " chickens");
        msg->setWindowTitle("Game Over!");
        scene()->clear();
        msg->exec();
        QApplication::quit();
    }
}
