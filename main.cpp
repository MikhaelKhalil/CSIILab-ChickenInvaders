#include "player.h"
#include <QApplication>
#include <QAudioOutput>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // *******  Create the View ********
    QGraphicsView view;
    view.setFixedSize(800, 600);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ******* Create the Scene ********
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    // *******  Show the score and health of the Player ********
    QGraphicsTextItem *Score = new QGraphicsTextItem;
    Score->setFont(QFont("times", 16));
    Score->setDefaultTextColor(Qt::cyan);
    Score->setPlainText("Score: 0");
    scene.addItem(Score);

    QGraphicsTextItem *Health = new QGraphicsTextItem;
    Health->setFont(QFont("times", 16));
    Health->setDefaultTextColor(Qt::red);
    Health->setPlainText("Health: 3");
    Health->setPos(0, 30);
    scene.addItem(Health);

    // *******  Create the Player ********
    Player *player = new Player(Score, Health);
    player->setPixmap(QPixmap(":/assets/assets/imgs/ship.png").scaled(50, 87));
    scene.addItem(player);

    // *******  Setting the foucs to the Player ********
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // *******  Adjust the location of the Player (middle of the screen) ********
    player->setPos(scene.width() / 2, scene.height() - 85);

    // *******   Assign scene to the view   ***************
    view.setScene(&scene);
    view.show();

    // *******  Create the Enemies automatically ********
    QTimer *time = new QTimer();
    QObject::connect(time, SIGNAL(timeout()), player, SLOT(createEnemy()));
    time->start(2000);

    // Play the main theme sound track
    QAudioOutput *mainThemeSoundOutput = new QAudioOutput;
    mainThemeSoundOutput->setVolume(1);
    QMediaPlayer *mainThemeSound = new QMediaPlayer;
    mainThemeSound->setAudioOutput(mainThemeSoundOutput);
    mainThemeSound->setSource(QUrl("qrc:/assets/assets/audio/theme.mp3"));
    mainThemeSound->setLoops(QMediaPlayer::Infinite);
    mainThemeSound->play();

    // Set the background of the scene
    QPixmap bg(":/assets/assets/imgs/bg.jpeg");
    scene.setBackgroundBrush(bg.scaled(800, 600));

    return a.exec();
}
