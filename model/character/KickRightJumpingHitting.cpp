#include "KickRightJumpingHitting.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "JumpingRight.h"
#include "BeingPushed.h"

KickRightJumpingHitting::KickRightJumpingHitting() {

}

KickRightJumpingHitting::~KickRightJumpingHitting() {

}

void KickRightJumpingHitting::update(MKCharacter *character, Events aEvent) {
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

float KickRightJumpingHitting::getWidth() {
    return 1.4;
}

string KickRightJumpingHitting::getName() {
	return "KickRightJumpingHitting";
}

bool KickRightJumpingHitting::isHitting() {
	return true;
}

bool KickRightJumpingHitting::impact() {
	return true;
}

bool KickRightJumpingHitting::isJumping() {
    return true;
}

bool KickRightJumpingHitting::isMovingRight() {
    return true;
}

void KickRightJumpingHitting::disableImpact(MKCharacter* character) {
    character->setState(new JumpingRight());
}