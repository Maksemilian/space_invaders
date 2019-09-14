#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;
class Player;
class EnemyGroup;
class Enemy;
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    static const quint16 SCENE_TIMOUT=200;

    static const quint16 SCREEN_MARGIN=200;
    static const quint16 SCENE_MARGIN=100;

    static const quint8 BOARD_OFFSET=50;
    static const quint8 ENEMY_OFFSET=10;

    static const quint8 ENEMY_SIZE_W=50;
    static const quint8 ENEMY_SIZE_H=50;

    static const quint8 PLAYER_SIZE_W=80;
    static const quint8 PLAYER_SIZE_H=80;

    static const quint8 COUNT_ROW_ENEMY=5;
    static const quint8 COUNT_COLUMN_ENEMY=8;

    static const QString PLAYER_LOST_STRING;
    static const QString PLAYER_WIN_STRING;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent*event) override;
private:
    QSize getScreenSize();
    void setSceneBoard(int w,int h);
    void setSceneBackground();


    void startGameTimer();
    void stopGameTimer();
    void setPlayer();
    void setEnemys();

    void startGame();
    void stopGame();
private slots:
    void onPlayerLost();
    void onPlayerWin();
    void onGameOver(const QString &text);
private:
    Ui::MainWindow *ui=nullptr;
    QGraphicsScene *scene=nullptr;
    QGraphicsView *view=nullptr;
    QTimer *sceneTimer=nullptr;
    Player *player=nullptr;
    EnemyGroup *enemyGroup=nullptr;
};

#endif // MAIN_WINDOW_H
