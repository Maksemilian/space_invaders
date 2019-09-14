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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene),
    view(new QGraphicsView(scene)),
    timer(new QTimer)
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

    int screenW=screen->size().width()-200;
    int screenH=screen->size().height()-200;
    return {screenW,screenH};
}

void MainWindow::setSceneBackground()
{
    QPixmap bg("D:\\QtProject\\SI\\yneg.png");
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

    int gameSceneW=size.width()-100;
    int gameSceneH=size.height()-100;

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
    connect(timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    timer->start(200);
    enemyGroup->startAttack();
}

void MainWindow::stopGameTimer()
{
    enemyGroup->stopAttack();
    timer->stop();
    disconnect(timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
}

void MainWindow::setPlayer()
{
    player=new Player;
    scene->addItem(player);
    player->setPos(0,scene->height()/2-BOARD_OFFSET);
    player->setData(0,GO_PLAYER);
    connect(player,&Player::dead,this,&MainWindow::onPlayerLost);
}

void MainWindow::setEnemys()
{
    enemyGroup=new EnemyGroup;

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
    int answer= QMessageBox::question(this,"Game over",text+" , reset game",
                                      QMessageBox::Yes,QMessageBox::No);
    if(answer==QMessageBox::Yes){
        stopGame();
        startGame();
    }else {
        stopGame();
        this->close();
    }
}

void MainWindow::onEnemyKill()
{
    Enemy*enemy= qobject_cast<Enemy*>(sender());
    if(enemy){
        enemys.removeOne(enemy);
        enemy->deleteLater();
    }
    if(enemys.isEmpty()){
        onPlayerWin();
    }
}

void MainWindow::onPlayerLost()
{
    onGameOver("Player Lost");
}

void MainWindow::onPlayerWin()
{
    onGameOver("Player Win");
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
