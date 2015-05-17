//
// Created by mauri on 17/05/15.
//

#include "Jumping.h"

Jumping::Jumping() {
    this->timer = 10;
}

Jumping::~Jumping() {
}

void Jumping::update(Character* character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingRight
    //delete character->state;
    //character->state = new MovingRight();

}
