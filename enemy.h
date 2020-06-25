#ifndef ENEMY_H
#define ENEMY_H


#include "pixmap_item.h"
class Bulet;
class QSize;

class Enemy : public PixmapItem
        //public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Enemy();
    void attack();
    void setDamage(Bulet *bulet);
signals:
    void dead();
protected:
    void advance(int shape) override;
private:
//    int _w=0;
//    int _h=0;
    QTimer *attackTimer;
    int reloadingTime=0;
    int speedX=20;
    int speedY=20;
};

#endif // ENEMY_H
