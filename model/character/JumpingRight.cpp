#include "JumpingRight.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "PunchRightJumping.h"

JumpingRight::JumpingRight() {
}

JumpingRight::~JumpingRight() {
}

void JumpingRight::update(MKCharacter * character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingRight
    //delete character->state;
    //character->state = new MovingRight();

    switch (aEvent) {
        case HighPunch:
            character->setState(new PunchRightJumping());
            break;
        case LowPunch:
            character->setState(new PunchRightJumping());
            break;
        case ReceiveHit:
            //cambiar a estado a beingHitJumpingRight
            character->setState(new ReceivingDuckingPunch());
            break;
        case JumpFinished:
            character->setState(new CharacterStance());
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }

}

bool JumpingRight::isJumping() {
    return true;
}

string JumpingRight::getName() {
    return "JumpingRight";
}

bool JumpingRight::isMovingRight() {
    return true;
}
