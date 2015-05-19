#include "Jumping.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"

Jumping::Jumping() {
}

Jumping::~Jumping() {
}

void Jumping::update(MKCharacter * character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingRight
    //delete character->state;
    //character->state = new MovingRight();

    switch (aEvent) {
        case ReceiveHit:
            //cambiar a estado a beingHitJumping
            character->setState(new ReceivingDuckingPunch());
            break;
        case JumpFinished:
            character->setState(new CharacterStance());
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
