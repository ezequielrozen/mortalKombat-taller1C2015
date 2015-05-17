#include <iostream>
#include "CharacterStance.h"
#include "MovingRight.h"
#include "MovingLeft.h"

CharacterStance::CharacterStance() {
//    this->timer = -1
}

CharacterStance::~CharacterStance() {

}

void CharacterStance::update(Character* character, Events aEvent) {
//    delete character->state; no estoy seguro si está bien, pero la idea es que como se cambia de estado, liberamos la memoria del anterior. no es costoso hacer estos news.
/*
    character->setState(new MovingRight());
*/    std::cout << "Update desde StanceState." << std::endl;

    switch (aEvent) {
        case MoveRight:
            //cambiar a estaro movingRight
            break;
        case MoveLeft:
            //cambiar a estado a movingLeft
            break;
        case Jump:
            //cambiar a estado jumping
            break;
        case Duck:
            //cambiar a estado a ducking
            break;
        case HighPunch:
            //cambiar a estado a highPunching
            break;
        case LowPunch:
            //cambiar a estado a lowPunching
            break;
        case HighKick:
            //cambiar a estado a highKicking
            break;
        case LowKick:
            //cambiar a estado a lowKicking
            break;
        case Block:
            //cambiar a estado a blocking
            break;
        case Shoot:
            //cambiar a estado a shooting
            break;
        case ReceiveHit:
            //cambiar a estado a beingHit
            break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}

void CharacterStance::getState() {
    std::cout << "Stance State." << endl;
}