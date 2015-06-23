#include "KickLeftJumpingHitting.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "JumpingLeft.h"
#include "BeingPushed.h"

KickLeftJumpingHitting::KickLeftJumpingHitting() {

}

KickLeftJumpingHitting::~KickLeftJumpingHitting() {

}

void KickLeftJumpingHitting::update(MKCharacter *character, Events aEvent) {
    switch (aEvent) {
        case JumpFinished:
            character->setState(new CharacterStance());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceivingFlyHit:
            if (character->getName() == "scorpion") {
                character->setState(new BeingPushed());
            }
            break;
        default:
            break;
    }
}

float KickLeftJumpingHitting::getWidth() {
    return 1.4;
}

string KickLeftJumpingHitting::getName() {
	return "KickLeftJumpingHitting";
}

bool KickLeftJumpingHitting::isHitting() {
	return true;
}

bool KickLeftJumpingHitting::impact() {
	return true;
}

bool KickLeftJumpingHitting::isJumping() {
    return true;
}

bool KickLeftJumpingHitting::isMovingLeft() {
    return true;
}

void KickLeftJumpingHitting::disableImpact(MKCharacter* character) {
    character->setState(new JumpingLeft());
}

