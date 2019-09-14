#include "enemy.h"
#include "bulet.h"

#include <constant.h>

#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include <QSize>

Enemy::Enemy(const QPointF &position,const QSize &size)
    :_w(size.width()),_h(size.height()),
      attackTimer(new QTimer),reloadingTime(1000)
{
    setPos(position);
//    connect(attackTimer,&QTimer::timeout,this,&Enemy::attack);
//    attackTimer->start(reloadingTime);
}

void Enemy::advance(int shape)
{
    QList<QGraphicsItem*> items=collidingItems();
    for (QGraphicsItem*item:items)
    {
        if(item->data(0)==GO_LEFT_BOARD||
                item->data(0)==GO_RIGHT_BOARD)
        {
//            setY(y()+speedY);
//            speedX=(-speedX);
        }
        else if(item->data(0)==GO_BULET_PLAYER)
        {
            Bulet *bulet=qgraphicsitem_cast<Bulet*>(item);
            if(bulet)
            {
                qDebug()<<"SET DAMAGE TO ENEMY";
                setDamage(bulet);
            }
        }
        else if(item->data(0)==GO_BOTTOM_BOARD)
        {
            qDebug()<<"********ENAMY GROUP WIN";
        }
    }
//    qDebug()<<"ENEMY"<<x()<<y();
//    setX(x()+speedX);
}

void Enemy::attack()
{
//    Bulet*bulet=new Bulet( QPointF(x(),y()+SIZE_H/2+50),90,speedY+10);
    QPointF pos=scenePos();
    pos.ry()+=SIZE_H/2+50;
    Bulet*bulet=new Bulet( pos,90,speedY+10);
    bulet->setData(0,GO_BULET_ENEMY);

    scene()->addItem(bulet);
}

void Enemy::setDamage(Bulet *bulet)
{
    bulet->deleteLater();
    deleteLater();
}

QRectF Enemy::boundingRect() const
{
    return  QRectF(0,0,SIZE_W,SIZE_H);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix("D:\\QtProject\\SI\\ship_enemy.png");
    painter->drawPixmap(0,0,SIZE_W,SIZE_H,pix);
    //    painter->setPen(Qt::gray);
    //    painter->setBrush(Qt::gray);
    //    painter->drawRect(0,0,50,20);
}
