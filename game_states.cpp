#include "game_states.h"
#include "graphics_scene.h"

#include <QStateMachine>

PlayState::PlayState(GraphicsScene* scene,QState* parent)
    :QState (parent),scene(scene)
{

}

void PlayState::onEntry(QEvent *)
{
    if(machine){
        machine->stop();
        scene->clear();
        delete machine;
    }

    machine = new QStateMachine;
}
