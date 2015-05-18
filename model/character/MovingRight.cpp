#include "MovingRight.h"
#include "CharacterStance.h"

MovingRight::MovingRight() {
//    this->timer =
}

MovingRight::~MovingRight() {
}

void MovingRight::update(MKCharacter * character, Events aEvent) {
//    delete character->state; no estoy seguro si está bien, pero la idea es que como se cambia de estado, liberamos la memoria del anterior. no es costoso hacer estos news.
/*
    character->setState(new MovingRight());
*/    std::cout << "Update desde MovingRight." << std::endl;
    switch (aEvent) {
        case Jump:
            //cambiar a estado jumpingRight (bolita)
            break;
        case LowPunch:
            //cambiar a estado a lowPunchingJumpig
            break;
        case LowKick:
            //cambiar a estado a lowKicking
            break;
        case ReceiveHit:
            //cambiar a estado a beingHit
            break;
        case MoveRightRelease:
            character->setState(new CharacterStance());
            // cambiar a estado stance
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}
