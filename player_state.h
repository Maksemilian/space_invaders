#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H
//Own
#include "player.h"
#include "bulet.h"
//#include "graphicsscene.h"
#include <QState>
#include <QDebug>
#include <QGraphicsScene>
// Qt
#include <QtWidgets/QKeyEventTransition>

class LaunchState :public QState
{
public:
    explicit LaunchState(Player*player,QState* parent=nullptr):
        QState(parent),player(player)
    {

    }

    void onEntry(QEvent *) override
    {
        qDebug("LaunchState");
        qDebug()<<"FIRE";
        Bulet*bulet=new Bulet(-90,30);
        bulet->setPos(player->x()+player->size().width()/2-50,
                      player->y()+player->size().height()/2-50);
        //        bulet->setData(0,GO_BULET_PLAYER);
        player->scene()->addItem(bulet);
    }
private:
    Player * player;
};
//This state is describing when the boat is moving right
class MoveStateRight : public QState
{
public:
    explicit MoveStateRight(Player *boat,QState *parent = 0) : QState(parent), boat(boat)
    {
    }
protected:
    void onEntry(QEvent *) override
    {
        //boat->setSpeed(5);
        qDebug()<<"MoveStateRight"<<boat->speed();
        boat->setCurrentDirection(Player::M_RIGHT);
        boat->updateMovement();
    }
private:
    Player * boat;
};

//This state is describing when the boat is moving left
class MoveStateLeft : public QState
{
public:
    explicit MoveStateLeft(Player *boat,QState *parent = 0) : QState(parent), boat(boat)
    {
    }
protected:
    void onEntry(QEvent *) override
    {
        qDebug("MoveStateLeft");
        //boat->setSpeed(5);
        boat->setCurrentDirection(Player::M_LEFT);
        boat->updateMovement();
    }
private:
    Player * boat;
};
//This state is describing when the boat is in a stand by position
class StopState : public QState
{
public:
    explicit StopState(Player *boat,QState *parent = 0)
        : QState(parent), boat(boat)
    {
    }
protected:
    void onEntry(QEvent *) override
    {
        qDebug("StopState");
        boat->setSpeed(0);
        boat->setCurrentDirection(Player::M_NONE);
        boat->updateMovement();
    }
private:
    Player * boat;
};

//************ TRANSITION ******************

class KeyLaunchTransition : public QKeyEventTransition
{
public:
    KeyLaunchTransition(Player *boat, QEvent::Type type, int key)
        : QKeyEventTransition(boat, type, key), boat(boat)
    {
    }
protected:
    bool eventTest(QEvent *event) override
    {
        qDebug()<<"KeyLaunchtransition"<<QKeyEventTransition::eventTest(event);
        if (!QKeyEventTransition::eventTest(event))
            return false;
        //We have enough bomb?
        //       return (boat->bombsLaunched() < MAX_BOMB);
        return  true;
    }
private:
    Player * boat;
};

//These transtion test if we have to stop the boat (i.e current speed is 1)
class KeyStopTransition : public QKeyEventTransition
{
public:
    KeyStopTransition(Player *b, QEvent::Type t, int k,const QString &name="name")
        : QKeyEventTransition(b, t, k), boat(b)
    {
        setObjectName(name);
    }
protected:
    bool eventTest(QEvent *event) override
    {
        qDebug()<<"KeyStopTransition"<<objectName()<<"Key:"<<key();
        if (!QKeyEventTransition::eventTest(event))
            return false;
        //return (boat->speed() == 0);
        return (boat->speed() == 1);
        //        return true;
    }
private:
    Player* boat;
};

class KeyMoveTransition : public QKeyEventTransition
{
public:
    KeyMoveTransition(Player *b, QEvent::Type t, int k,const QString &name="name")
        : QKeyEventTransition(b, t, k), boat(b), key(k)
    {
        setObjectName(name);
    }
protected:
    bool eventTest(QEvent *event) override
    {
        qDebug()<<"KeyMoveTransition::eventTest"
               <<QKeyEventTransition::eventTest(event)<<
                 boat->speed()<<objectName()<<"Key:"<<key;
        if (!QKeyEventTransition::eventTest(event))
            return false;
        return (boat->speed() >= 0);
        //        return true;
    }
    void onTransition(QEvent *) override
    {
        qDebug("KeyMoveTransition");
        /*  boat->setSpeed(5);
        if (key == Qt::Key_Left && boat->currentDirection() == Player::M_RIGHT){
            boat->setCurrentDirection(Player::M_LEFT);
            //            boat->setSpeed(boat->speed()-1);
            qDebug()<<"LEFT:"<<key;
        }
        else if (key == Qt::Key_Right && boat->currentDirection() == Player::M_LEFT){
            boat->setCurrentDirection(Player::M_RIGHT);
            //            boat->setSpeed(boat->speed()-1);
            qDebug()<<"RIGHT:"<<key;
        }else if (boat->speed()<3) {
            qDebug()<<"ELSE"<<boat->speed();
            boat->setSpeed(boat->speed()+1);
        }

        boat->updateMovement();
        qDebug()<<"Speed:"<<boat<<boat->speed();*/
        //        We decrease the speed if needed

        if (key == Qt::Key_Left && boat->currentDirection() ==
                Player::M_RIGHT)
        {
            boat->setSpeed(boat->speed() - 1);
        }
        else if (key == Qt::Key_Right && boat->currentDirection() ==
                 Player::M_LEFT)
        {
            boat->setSpeed(boat->speed() - 1);
        }
        else if (boat->speed() < 3)
        {
            boat->setSpeed(boat->speed() + 1);
        }
        boat->updateMovement();
    }
private:
    Player * boat;
    int key;
};


#endif // PLAYER_STATE_H
