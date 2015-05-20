#include "KickRightJumpingHitting.h"
#include "CharacterStance.h"

KickRightJumpingHitting::KickRightJumpingHitting() {

}

KickRightJumpingHitting::~KickRightJumpingHitting() {

}

void KickRightJumpingHitting::update(MKCharacter *character, Events aEvent) {
    switch (aEvent) {
        case JumpFinished:
            character->setState(new CharacterStance());
        default:
            break;
    }
}

float KickRightJumpingHitting::getWidth() {
    return 0;
}

string KickRightJumpingHitting::getName() {
	return "KickRightJumping";
}
