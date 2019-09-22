#include "main_window.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "player.h"
#include "constant.h"
#include "enemy.h"
#include "enemy_group.h"

#include <QKeyEvent>
#include <QDebug>
#include <QScreen>
#include <QTimer>
#include <QMessageBox>

const QString  MainWindow::PLAYER_LOST_STRING="Player lost";
const QString MainWindow::PLAYER_WIN_STRING="Player win";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene),
    view(new QGraphicsView(scene)),
    sceneTimer(new QTimer)
{
    ui->setupUi(this);
    setCentralWidget(view);

    QSize size=getScreenSize();
    setFixedSize(size.width(),size.height());

    startGame();
}

QSize MainWindow::getScreenSize()
{
    QScreen *screen=QApplication::screens().at(0);

    int screenW=screen->size().width()-SCREEN_MARGIN;
    int screenH=screen->size().height()-SCREEN_MARGIN;
    return {screenW,screenH};
}

void MainWindow::setSceneBackground()
{
    QPixmap bg(":images/space_background.png");
    scene->setBackgroundBrush(QBrush(bg));
}

void MainWindow::setSceneBoard(int  gameSceneW,int gameSceneH)
{
    scene->setSceneRect(-gameSceneW/2,-gameSceneH/2,gameSceneW,gameSceneH);
    //left line
    scene->addLine(-gameSceneW/2,gameSceneH/2,
                   -gameSceneW/2,-gameSceneH/2)->setData(0,GO_LEFT_BOARD);

    //right line
    scene->addLine(gameSceneW/2,gameSceneH/2,
                   gameSceneW/2,-gameSceneH/2)->setData(0,GO_RIGHT_BOARD);

    //bottom line
    scene->addLine(-gameSceneW/2,gameSceneH/2,
                   gameSceneW/2,gameSceneH/2)->setData(0,GO_BOTTOM_BOARD);
    //    top line
    scene->addLine(-gameSceneW/2,-gameSceneH/2,
                   gameSceneW/2,-gameSceneH/2)->setData(0,GO_TOP_BOARD);

}

void MainWindow::startGame()
{
    QSize size=getScreenSize();

    int gameSceneW=size.width()-SCENE_MARGIN;
    int gameSceneH=size.height()-SCENE_MARGIN;

    setSceneBoard(gameSceneW,gameSceneH);
    setSceneBackground();
    setPlayer();
    setEnemys();
    startGameTimer();
}

void MainWindow::stopGame()
{
    stopGameTimer();
    scene->clear();
}

void MainWindow::startGameTimer()
{
    connect(sceneTimer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    sceneTimer->start(SCENE_TIMOUT);
    enemyGroup->startAttack();
}

void MainWindow::stopGameTimer()
{
    enemyGroup->stopAttack();
    sceneTimer->stop();
    disconnect(sceneTimer,&QTimer::timeout,scene,&QGraphicsScene::advance);
}

void MainWindow::setPlayer()
{
    player=new Player(QPointF(0,scene->height()/2-PLAYER_SIZE_H),
                      QSize(PLAYER_SIZE_W,PLAYER_SIZE_H));
    scene->addItem(player);
    player->setData(0,GO_PLAYER);

    connect(player,&Player::dead,
            this,&MainWindow::onPlayerLost);
}

void MainWindow::setEnemys()
{
    enemyGroup=new EnemyGroup;

    connect(enemyGroup,&EnemyGroup::dead,
            this,&MainWindow::onPlayerWin);

    const int countEnemyRow=COUNT_ROW_ENEMY;
    const int countEnemyCollumn=COUNT_COLUMN_ENEMY;

    const qreal leftPosX=(-scene->width()/2+BOARD_OFFSET);
    const qreal leftPosY=(-scene->height()/2+BOARD_OFFSET);

    const int dY=ENEMY_SIZE_H+ENEMY_OFFSET;
    const int dX=ENEMY_SIZE_W+ENEMY_OFFSET;

    qreal maxPosX=leftPosX+countEnemyCollumn*dX;
    qreal maxPosY=leftPosY+countEnemyRow*dY;

    for(qreal posY=leftPosY;posY<maxPosY;posY+=dY){
        for(qreal posX=leftPosX;posX<maxPosX;posX+=dX){
            Enemy *enemy=new Enemy(QPointF(posX,posY),
                                   QSize(ENEMY_SIZE_W,ENEMY_SIZE_H));
            enemy->setData(0,GO_ENEMY);
            enemyGroup->addToGroup(enemy);
        }
    }
    scene->addItem(enemyGroup);
}

void MainWindow::onGameOver(const QString &text)
{
    int answer= QMessageBox::question(this,"Game over",text+" , Let's go new game",
                                      QMessageBox::Yes,QMessageBox::No);

//    stopGame();
    if(answer==QMessageBox::Yes){
        //TODO ПРОИСХОДИТ КРАХ ПРОГРАММЫ
        //ВО ВРЕМЯ ОСВОБОЖДЕНИЯ РЕСУРСОВ

        stopGame();
        startGame();
    }
    else {
        stopGame();
        this->close();}
}

void MainWindow::onPlayerLost()
{
    onGameOver(PLAYER_LOST_STRING);
}

void MainWindow::onPlayerWin()
{
    onGameOver(PLAYER_WIN_STRING);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!player)return;
    qDebug()<<"Key"<<event->key();
    switch (event->key()) {
    case Qt::Key_A:
        player-> moveLeft();
        break;

    case Qt::Key_D:
        player->  moveRight();
        break;

    case Qt::Key_Space:
        player->  attack();
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
