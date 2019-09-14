#include "bulet.h"
#include "constant.h"
#include "enemy.h"
#include "player.h"

#include <QPainter>
#include <QGraphicsScene>

Bulet::Bulet(const QPointF &start,qreal rotate,int speed,QObject *parent):
    QObject (parent),QGraphicsItem (),_rotate(rotate),_speed(speed)
{
    setPos(start);
}

QRectF Bulet::boundingRect() const
{
    return QRectF(0,0,SIZE_W,SIZE_H);
}

void Bulet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString path;
    if(_rotate>0){
        path="D:\\QtProject\\SI\\missile_enemy.png";
    }else {
         path="D:\\QtProject\\SI\\missile_player.png";
    }
    QPixmap pix(path);

    painter->drawPixmap(0,0,SIZE_W,SIZE_H,pix);
//    painter->rotate(90);
}

void Bulet::advance(int phase)
{
    if(!phase) return;

    if(_rotate>0){
        setY(y()+_speed);
    }else {
        setY(y()-_speed);
    }

    if(y()>=scene()->height()/2||
            y()<=-scene()->height()/2)
        deleteLater();
}
