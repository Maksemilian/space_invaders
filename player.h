#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QObject>

class Bulet;

class Player :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Player(const QPointF &pos,const QSize &size);
    void moveRight();
    void moveLeft();
    void attack();
    void setDamage(Bulet *bulet);
signals:
    void dead();
protected:
    void advance(int shape)override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget)override;
//    void keyPressEvent(QKeyEvent*event) override;
private:
    bool collidingWithBoard();
private:
    quint8 _speed=0;
    int _w=0;
    int _h=0;
};

#endif // PLAYER_H
