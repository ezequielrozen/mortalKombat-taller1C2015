//
// Created by mauri on 17/05/15.
//

#include "Ducking.h"

Ducking::Ducking() {
    this->timer = 10;
}

Ducking::~Ducking() {
}

void Ducking::update(MKCharacter * character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingRight
    //delete character->state;
    //character->state = new MovingRight();
    switch (aEvent) {
        case Jump:
            //cambiar a estado jumping
            break;
        case LowPunch:
            //cambiar a estado a lowPunching
            break;
        case LowKick:
            //cambiar a estado a lowKicking
            break;
        case ReceiveHit:
            //cambiar a estado a beingHit
            break;
        case DuckRelease:
            // cambiar a estado stance
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}

