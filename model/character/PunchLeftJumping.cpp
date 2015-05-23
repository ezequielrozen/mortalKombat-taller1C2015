#include "PunchLeftJumping.h"
#include "JumpingLeft.h"

PunchLeftJumping::PunchLeftJumping() {

}

PunchLeftJumping::~PunchLeftJumping() {

}

void PunchLeftJumping::update(MKCharacter *character, Events aEvent) {
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

string PunchLeftJumping::getName() {
	return "PunchLeftJumping";
}

float PunchLeftJumping::getWidth() {
    return 1.4;
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

bool PunchLeftJumping::impact() {
    return true;
}

void PunchLeftJumping::disableImpact(MKCharacter* character) {
    character->setState(new JumpingLeft());
}