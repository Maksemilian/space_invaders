#include "player.h"
#include "player_state.h"

#include "constant.h"
#include "bulet.h"

#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QHistoryState>

Player::Player()
    :PixmapItem ("ship_player.png"),
      _speed(0)
{
//    qDebug()<<"CTONSTRUCT_SPEED"<<this<<_speed;

    setZValue(4);
    setFlags(QGraphicsItem::ItemIsFocusable);

    //TODO понять как работает Animation
    //The movement animation used to animate the boat
    movementAnimation = new QPropertyAnimation(this, "pos");

    //The destroy animation used to explode the boat
    // destroyAnimation = setupDestroyAnimation(this);

    //We setup the state machine of the boat
    machine = new QStateMachine(this);
    QState *moving = new QState(machine);
    StopState *stopState = new StopState(this,moving);
    machine->setInitialState(moving);
    moving->setInitialState(stopState);

    MoveStateRight *moveStateRight = new MoveStateRight(this,moving);
    MoveStateLeft *moveStateLeft= new MoveStateLeft(this,moving);

    //then setup the transitions for the rightMove state
    KeyStopTransition *leftStopRight = new KeyStopTransition(this, QEvent::KeyPress, Qt::Key_Left);
    leftStopRight->setTargetState(stopState);
    KeyMoveTransition *leftMoveRight = new KeyMoveTransition(this, QEvent::KeyPress, Qt::Key_Left);
    leftMoveRight->setTargetState(moveStateRight);

    KeyMoveTransition *rightMoveRight = new KeyMoveTransition(this,
                                                              QEvent::KeyPress,
                                                              Qt::Key_Right);
    rightMoveRight->setTargetState(moveStateRight);
    KeyMoveTransition *rightMoveStop = new KeyMoveTransition(this,
                                                             QEvent::KeyPress,
                                                             Qt::Key_Right);
    rightMoveStop->setTargetState(moveStateRight);

    //then setup the transitions for the leftMove state
    KeyStopTransition *rightStopLeft = new KeyStopTransition(this,
                                                             QEvent::KeyPress,
                                                             Qt::Key_Right);
    rightStopLeft->setTargetState(stopState);
    KeyMoveTransition *rightMoveLeft = new KeyMoveTransition(this, QEvent::KeyPress, Qt::Key_Right);
    rightMoveLeft->setTargetState(moveStateLeft);
    KeyMoveTransition *leftMoveLeft = new KeyMoveTransition(this, QEvent::KeyPress,Qt::Key_Left);
    leftMoveLeft->setTargetState(moveStateLeft);
    KeyMoveTransition *leftMoveStop = new KeyMoveTransition(this, QEvent::KeyPress,Qt::Key_Left);
    leftMoveStop->setTargetState(moveStateLeft);

    //We set up the right move state
    moveStateRight->addTransition(leftStopRight);
    moveStateRight->addTransition(leftMoveRight);
    moveStateRight->addTransition(rightMoveRight);
    stopState->addTransition(rightMoveStop);

    //We set up the left move state
    moveStateLeft->addTransition(rightStopLeft);
    moveStateLeft->addTransition(leftMoveLeft);
    moveStateLeft->addTransition(rightMoveLeft);
    stopState->addTransition(leftMoveStop);

    // ********* RIGHT
/*
    KeyMoveTransition *leftMoveRight = new KeyMoveTransition(this, QEvent::KeyPress, Qt::Key_Left);
    leftMoveRight->setTargetState(moveStateRight);

    KeyStopTransition *leftStopRight = new KeyStopTransition(this,
                                                             QEvent::KeyPress,
                                                             Qt::Key_Left,
                                                             "LeftStopRight");
    leftStopRight->setTargetState(stopState);
    KeyMoveTransition *rightMoveRight = new KeyMoveTransition(this,
                                                              QEvent::KeyPress,
                                                              Qt::Key_Right,
                                                              "RightMoveRight");
    rightMoveRight->setTargetState(moveStateRight);

    KeyMoveTransition *stopMoveRight = new KeyMoveTransition(this,
                                                             QEvent::KeyPress,
                                                             Qt::Key_Right,
                                                             "StopMoveRight");
    stopMoveRight->setTargetState(moveStateRight);

    moveStateRight->addTransition(leftStopRight);
//    moveStateRight->addTransition(leftMoveRight);
    moveStateRight->addTransition(rightMoveRight);
    stopState->addTransition(stopMoveRight);


    //********** LEFT
    KeyMoveTransition *rightMoveLeft = new KeyMoveTransition(this, QEvent::KeyPress, Qt::Key_Right);
    rightMoveLeft->setTargetState(moveStateRight);

    KeyStopTransition *rightStopLeft = new KeyStopTransition(this,
                                                             QEvent::KeyPress,
                                                             Qt::Key_Right);
    rightStopLeft->setTargetState(stopState);
    KeyMoveTransition *leftMoveLeft = new KeyMoveTransition(this,
                                                            QEvent::KeyPress,
                                                            Qt::Key_Left);
    leftMoveLeft->setTargetState(moveStateLeft);

    KeyMoveTransition *stopMoveLeft = new KeyMoveTransition(this,
                                                            QEvent::KeyPress,
                                                            Qt::Key_Left);
    stopMoveLeft->setTargetState(moveStateLeft);

    moveStateLeft->addTransition(rightStopLeft);
//    moveStateLeft->addTransition(rightMoveLeft);
    moveStateLeft->addTransition(leftMoveLeft);
    stopState->addTransition(stopMoveLeft);
*/

    //*********** FIRE
    LaunchState *launchState=new LaunchState(this,machine);
    KeyLaunchTransition *launchTransitionRight=new KeyLaunchTransition(this,
                                                                       QEvent::KeyPress,
                                                                       Qt::Key_Up);
    launchTransitionRight->setTargetState(launchState);

    KeyLaunchTransition *launchTransitionLeft=new KeyLaunchTransition(this,
                                                                      QEvent::KeyPress,
                                                                      Qt::Key_Up);
    launchTransitionLeft->setTargetState(launchState);


    KeyLaunchTransition *launchTransitionStop=new KeyLaunchTransition(this,
                                                                      QEvent::KeyPress,
                                                                      Qt::Key_Up);
    launchTransitionStop->setTargetState(launchState);

    moveStateRight->addTransition(launchTransitionRight);
    moveStateLeft->addTransition(launchTransitionLeft);
    stopState->addTransition(launchTransitionStop);

    QHistoryState *historyState = new QHistoryState(moving);
    launchState->addTransition(historyState);

}

void Player::run()
{
    machine->start();
}

void Player::stop()
{
    movementAnimation->stop();
    machine->stop();
}

void Player::setCurrentDirection(Movement direction)
{
    _direction=direction;
}

void Player::updateMovement()
{
    if (_speed == 0 || _direction == Player::M_NONE) {
        movementAnimation->stop();
        return;
    }

    movementAnimation->stop();

        //TODO понять как задаются границы и скорость
    if (_direction == Player::M_LEFT) {
        movementAnimation->setEndValue(QPointF(0,y()));
//        movementAnimation->setEndValue(QPointF(scene()->sceneRect().right()+size().width(),y()));
        movementAnimation->setDuration(x()/_speed*15);
    }
    else /*if (direction == Boat::Right)*/ {
        movementAnimation->setEndValue(QPointF(scene()->width()-size().width(),y()));
//        movementAnimation->setEndValue(QPointF(scene()->sceneRect().left()-size().width(),y()));
        movementAnimation->setDuration((scene()->width()-size().width()-x())/_speed*15);
    }
    movementAnimation->start();
/*
    if (_speed == 0 || _direction == Player::M_NONE) {
        //movementAnimation->stop();
        qDebug()<<"PLAYER STOP"<<this<<_speed;
        return;
    }
    if(_direction==M_LEFT){
        moveLeft();
    }else if(_direction==M_RIGHT){
        moveRight();

    }
    */
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
    qDebug()<<"Move_Right"<<_speed;
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
/*
void Player::attack()
{
    Bulet*bulet=new Bulet(-90,30);
    bulet->setPos(x()+size().width()/2-50,y()+size().height()/2-50);
    bulet->setData(0,GO_BULET_PLAYER);
    scene()->addItem(bulet);
}

void Player::setDamage(Bulet *bulet)
{
    qDebug()<<"Player Set Damage";
    bulet->deleteLater();
    //    deleteLater();
}*/
/*
QRectF Player::boundingRect() const
{
    return QRectF(0,0,_w,_h);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPixmap pix(":/images/ship_player.png");
    QPixmap pix(":images/ship_player.png");
    painter->drawPixmap(0,0,_w,_h,pix);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
*/
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
