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
    static const quint8 BOARD_OFFSET=50;
    static const quint8 ENEMY_OFFSET=10;

    static const quint8 ENEMY_SIZE_W=50;
    static const quint8 ENEMY_SIZE_H=50;

    static const quint8 COUNT_ROW_ENEMY=5;
    static const quint8 COUNT_COLUMN_ENEMY=8;

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
    void onEnemyKill();
    void onGameOver(const QString &text);
private:
    Ui::MainWindow *ui=nullptr;
    QGraphicsScene *scene=nullptr;
    QGraphicsView *view=nullptr;
    QTimer *timer=nullptr;
    Player *player=nullptr;
    EnemyGroup *enemyGroup=nullptr;
    QList<Enemy*>enemys;
};

#endif // MAIN_WINDOW_H
