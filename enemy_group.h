#ifndef ENEMY_GROUP_H
#define ENEMY_GROUP_H

#include <QObject>
#include <QGraphicsItemGroup>


class EnemyGroup :public QObject, public  QGraphicsItemGroup
{
    Q_OBJECT
public:
    EnemyGroup();
    void startAttack();
    void stopAttack();
signals:
    void collidingWithPlayer();
    void enemyGroupKilled();
protected:
    void advance(int shape)override;
private slots:
    void onAttack();
    void onEnemyDead();

private:
    int speedX=20;
    int speedY=20;
    QTimer *attackTimer;
};

#endif // ENEMY_GROUP_H
