#include "Jumping.h"

Jumping::Jumping() {
    this->timer = 10;
}

Jumping::~Jumping() {
}

void Jumping::update(MKCharacter * character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingRight
    //delete character->state;
    //character->state = new MovingRight();

    switch (aEvent) {
        case LowPunch:
            //cambiar a estado a lowPunchingJumping
            break;
        case LowKick:
            //cambiar a estado a lowKickingJumping
            break;
        case ReceiveHit:
            //cambiar a estado a beingHitJumping
            break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }

}

bool Jumping::isJumping() {
    return true;
}

string Jumping::getName() {
    return "Jumping";
}

float Jumping::getWidth() {
    return 0;
}