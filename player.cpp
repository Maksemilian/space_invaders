#include "player.h"
#include "constant.h"
#include "bulet.h"

#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>


Player::Player(const QPointF &pos,const QSize &size)
    :_speed(10),_w(size.width()),_h(size.height())
{
    setPos(pos);
}

void Player::moveLeft()
{
    //    if(!collidingWithBoard())
    setX(x()-_speed);
    collidingWithBoard();
}

void Player::moveRight()
{
    //    if(!collidingWithBoard())
    setX(x()+_speed);
    collidingWithBoard();
}

bool Player::collidingWithBoard()
{
    QRectF rect=scene()->sceneRect();
    qreal leftX=rect.x();
    qreal rightX=rect.x()+rect.width();

    if(x()<=leftX){
        setX(leftX+_speed);
    }else if(x()>=rightX){
        setX(rightX-_speed);
    }

    return false;
}

void Player::advance(int shape)
{
    //    if(!shape)return;

    QList<QGraphicsItem*>items= collidingItems();

    for(QGraphicsItem*item:items){

        if (item->data(0)==GO_ENEMY||
                item->data(0)==GO_BULET_ENEMY) {
            qDebug()<<"PLAYER LOAST";
            //            emit collidingWithPlayer();
            emit dead();
            return;
        }
    }
}

void Player::attack()
{
    Bulet*bulet=new Bulet( QPointF(x(),y()+_h/2-50),-90,30);
    bulet->setData(0,GO_BULET_PLAYER);
    scene()->addItem(bulet);
}

void Player::setDamage(Bulet *bulet)
{
    qDebug()<<"Player Set Damage";
    bulet->deleteLater();
    //    deleteLater();
}

QRectF Player::boundingRect() const
{
    return QRectF(0,0,_w,_h);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPixmap pix(":/images/ship_player.png");
    QPixmap pix(":/images/ship_player.png");
    painter->drawPixmap(0,0,_w,_h,pix);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/*
void Player::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"Key"<<event->key();
    switch (event->key()) {
    case Qt::Key_A:
        moveLeft();
        break;

    case Qt::Key_D:
        moveRight();
        break;

    case Qt::Key_Space:
        attack();
        break;
    }
}
*/
