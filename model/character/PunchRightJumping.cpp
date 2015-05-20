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
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case JumpFinished:
            character->setState(new CharacterStance());
            break;
        default:
            break;
    }
}

float PunchRightJumping::getWidth() {
    return 1.4;
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

bool PunchRightJumping::impact() {
    return true;
}

string PunchRightJumping::getName() {
	return "PunchRightJumping";
}
