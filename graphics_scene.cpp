#include "graphics_scene.h"
#include "player.h"
#include "game_states.h"

#include <QTimer>
#include <QAction>
#include <QStateMachine>
#include <QFinalState>
#include <QApplication>

const QString GraphicsScene::PLAYER_LOST_STRING="Player lost";
const QString GraphicsScene::PLAYER_WIN_STRING="Player win";


GraphicsScene::GraphicsScene(int x,int y,qreal width,qreal heigh)
    :QGraphicsScene(x,y,width,heigh),player(new Player()), moveTimer(new QTimer)
{
    QPixmap bg(":images/space_background.png");
    setBackgroundBrush(QBrush(bg));

    player->setPos(0,height()/2-player->size().height());
    addItem(player);

    player->show();
    player->run();
    startGameTimer();
}

void GraphicsScene::clear()
{
    player->deleteLater();
}

void GraphicsScene::setupScene(QAction * newGameAction,QAction *quitAction)
{
    QStateMachine *machine=new QStateMachine(this);
    PlayState *gameState=new PlayState(this,machine);
    QFinalState* finalState=new QFinalState(machine);

    gameState->addTransition(newGameAction,&QAction::triggered,gameState);
    gameState->addTransition(quitAction,&QAction::triggered,finalState);

    machine->setInitialState(gameState);
    machine->start();

    connect(machine,&QStateMachine::finished,qApp,&QApplication::quit);

}

void GraphicsScene::startGameTimer()
{
    connect(moveTimer,&QTimer::timeout,this,&QGraphicsScene::advance);
    moveTimer->start(SCENE_TIMOUT);
//    enemyGroup->startAttack();
}

void GraphicsScene::stopGameTimer()
{
//    enemyGroup->stopAttack();
    moveTimer->stop();
    disconnect(moveTimer,&QTimer::timeout,this,&QGraphicsScene::advance);
}
