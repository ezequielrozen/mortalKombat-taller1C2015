#include "PunchLeftJumping.h"

PunchLeftJumping::PunchLeftJumping() {

}

PunchLeftJumping::~PunchLeftJumping() {

}

void PunchLeftJumping::update(MKCharacter *character, Events aEvent) {
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

string PunchLeftJumping::getName() {
	return "PunchLeftJumping";
}

float PunchLeftJumping::getWidth() {
    return 1.2;
}

bool PunchLeftJumping::isJumping() {
    return true;
}

bool PunchLeftJumping::isMovingLeft() {
    return true;
}

bool PunchLeftJumping::isHitting() {
    return true;
}