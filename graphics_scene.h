#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include <QGraphicsScene>
class Player;
class QAction;
class GraphicsScene:public QGraphicsScene
{
        static const quint16 SCENE_TIMOUT=200;

        static const quint8 BOARD_OFFSET=50;
        static const quint8 ENEMY_OFFSET=10;

        static const quint8 ENEMY_SIZE_W=50;
        static const quint8 ENEMY_SIZE_H=50;

        static const quint8 PLAYER_SIZE_W=80;
        static const quint8 PLAYER_SIZE_H=80;

        static const quint8 COUNT_ROW_ENEMY=5;
        static const quint8 COUNT_COLUMN_ENEMY=8;

        static const QString PLAYER_LOST_STRING;
        static const QString PLAYER_WIN_STRING;

public:
    GraphicsScene(int x,int y,qreal width,qreal heigh);
    //TODO сделать передачу акшинов по которым будет запускатьс сцена
    void setupScene(QAction * newGameAction,QAction *quitAction);
    void clear();
private:
    void startGameTimer();
    void stopGameTimer();
private:
    Player *player;
    QTimer *moveTimer=nullptr;
};

#endif // GRAPHICS_SCENE_H
