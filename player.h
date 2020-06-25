#ifndef PLAYER_H
#define PLAYER_H

#include "pixmap_item.h"

class Bulet;
class QStateMachine;
class  QVariantAnimation;

class Player :public PixmapItem
{
    Q_OBJECT
    int MAX_ROCKET=1;
public:
    enum Movement{
        M_NONE = 0  ,
        M_RIGHT = 1,
        M_LEFT = 2
    };
    Player();
    void run();
    void stop();
    void setCurrentDirection(Movement direction);
    Movement currentDirection(){return _direction;}
    void updateMovement();
    inline void setSpeed(int speed){        _speed=speed;    }
    inline int speed(){return _speed; }
signals:
    void dead();
protected:
    void advance(int shape)override;
private:
    void moveRight();
    void moveLeft();
    bool collidingWithBoard();
private:
    int _speed=-1;
    Movement _direction=M_NONE;
    QStateMachine *machine;
    QVariantAnimation *movementAnimation;
};

#endif // PLAYER_H
