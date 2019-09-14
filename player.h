#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QObject>

class Bulet;

class Player :public QObject, public QGraphicsItem
{
    Q_OBJECT
    quint8 SIZE_W=80;
    quint8 SIZE_H=80;
public:
    Player();
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
    quint8 speed=0;
};

#endif // PLAYER_H
