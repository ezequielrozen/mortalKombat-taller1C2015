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
    switch (aEvent) {
        case Jump:
            //cambiar a estado jumpingLeft (bolita)
            break;
        case LowPunch:
            //cambiar a estado a lowPunching
            break;
        case HighPunch:
            //cambiar a estado a lowPunching
            break;
        case LowKick:
            //cambiar a estado a lowKicking
            break;
        case HighKick:
            //cambiar a estado a lowPunching
            break;
        case ReceiveHit:
            //cambiar a estado a beingHit
            break;
        case MoveLeftRelease:
            // cambiar a estado stance
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}