#include "JumpingLeft.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"

JumpingLeft::JumpingLeft() {
}

JumpingLeft::~JumpingLeft() {
}

void JumpingLeft::update(MKCharacter * character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingLeft
    //delete character->state;
    //character->state = new MovingLeft();

    switch (aEvent) {
        case ReceiveHit:
            //cambiar a estado a beingHitJumpingLeft
            character->setState(new ReceivingDuckingPunch());
            break;
        case JumpFinished:
            character->setState(new CharacterStance());
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }

}

bool JumpingLeft::isJumping() {
    return true;
}

string JumpingLeft::getName() {
    return "JUMPLEFT";
}

bool JumpingLeft::isMovingLeft() {
    cout << "MOVING LEFT" << endl;
    return true;
}


float JumpingLeft::getWidth() {
    return 0;
}