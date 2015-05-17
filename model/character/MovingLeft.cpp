#include "MovingLeft.h"

MovingLeft::MovingLeft() {
    this->timer = 10;
}

MovingLeft::~MovingLeft() {
}

void MovingLeft::update(Character* character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingRight
    //delete character->state;
    //character->state = new MovingRight();

}
