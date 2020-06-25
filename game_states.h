#ifndef GAME_STATES_H
#define GAME_STATES_H

#include <QState>

class  GraphicsScene;

class PlayState : public QState
{
public:
    explicit PlayState(GraphicsScene *scene, QState *parent = nullptr);
    ~PlayState();

 protected:
    void onEntry(QEvent *) override;

private :
    GraphicsScene *scene;
    QStateMachine *machine;
};

#endif // GAME_STATES_H
