#include "PunchRightJumping.h"

PunchRightJumping::PunchRightJumping() {

}

PunchRightJumping::~PunchRightJumping() {

}

void PunchRightJumping::update(MKCharacter *character, Events aEvent) {
    switch (aEvent) {
        case ReceiveHit:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case JumpFinished:
            character->setState(new CharacterStance());
        default:
            break;
    }
}

float PunchRightJumping::getWidth() {
    return 1.2;
}

bool PunchRightJumping::isJumping() {
    return true;
}

bool PunchRightJumping::isMovingRight() {
    return true;
}

bool PunchRightJumping::isHitting() {
    return true;
}

string PunchRightJumping::getName() {
	return "PunchRightJumping";
}
