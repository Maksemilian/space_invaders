#ifndef BULET_H
#define BULET_H

#include "pixmap_item.h"

//#include <QGraphicsItem>
//#include <QObject>

class Bulet:public PixmapItem
        //public QObject ,public QGraphicsItem
{
    Q_OBJECT
//    quint8 SIZE_W=10;
//    quint8 SIZE_H=30;
public:
    Bulet(qreal rotate,int speed);
protected:
//    QRectF boundingRect()const override;
    /*
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget)override;\
               */
    void advance(int sphase)override;
private:
    int _speed=30;
    qreal _rotate=0;
};

#endif // BULET_H
