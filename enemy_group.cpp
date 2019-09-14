#include "enemy_group.h"
#include "constant.h"
#include "enemy.h"

#include <ctime>

#include <QDebug>
#include <QTimer>
#include <QList>

EnemyGroup::EnemyGroup():attackTimer(new QTimer){}

void EnemyGroup::startAttack()
{
    connect(attackTimer,&QTimer::timeout,this,&EnemyGroup::onAttack);
    attackTimer->start(2000);
}

void EnemyGroup::stopAttack()
{
    disconnect(attackTimer,&QTimer::timeout,this,&EnemyGroup::onAttack);
    attackTimer->stop();
}

void EnemyGroup::onAttack()
{
    int attackerNumber=3;

    QList<QGraphicsItem*> children=childItems();
    int size=children.size();
    srand( time(  nullptr ) );
    for(int i=0;i<attackerNumber;i++){
        int childIndex=0 + rand() % (size -1);
        if(Enemy *enemy=qgraphicsitem_cast<Enemy*>(children[childIndex])){
            enemy->attack();
        }
    }
}

void EnemyGroup::onEnemyDead()
{
    qDebug()<<"Enemy dead"<<childItems().size();
    if(childItems().isEmpty())
        emit enemyGroupKilled();
}

void EnemyGroup::advance(int shape)
{
    if(!shape)return;

    QList<QGraphicsItem*> items=collidingItems();
    for (QGraphicsItem*item:items) {
        if(item->data(0)==GO_LEFT_BOARD||
                item->data(0)==GO_RIGHT_BOARD){
            setY(y()+speedY);
            speedX=(-speedX);
        }else if(item->data(0)==GO_BOTTOM_BOARD){
            qDebug()<<"********ENAMY GROUP WIN";
        }
    }
    qDebug()<<"PARENT ENEMY"<<x()<<y();
    setX(x()+speedX);
}
