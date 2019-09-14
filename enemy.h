#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QObject>
#include <QSize>

class Bulet;
class QSize;

class Enemy :public QObject, public QGraphicsItem
{
    Q_OBJECT
    quint8 SIZE_W=50;
    quint8 SIZE_H=50;
public:
    Enemy(const QPointF &position,const QSize &size);
    void attack();
    void setDamage(Bulet *bulet);
    inline QSize size(){return {SIZE_W,SIZE_H }; }
signals:
    void dead();
protected:
    void advance(int shape) override;
    QRectF boundingRect() const override;

    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,
               QWidget *widget)override;
private:
    int _w=0;
    int _h=0;
    QTimer *attackTimer;
    int reloadingTime=0;
    int speedX=20;
    int speedY=20;
};

#endif // ENEMY_H
