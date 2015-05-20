#include "KickLeftJumpingHitting.h"
#include "CharacterStance.h"

KickLeftJumpingHitting::KickLeftJumpingHitting() {

}

KickLeftJumpingHitting::~KickLeftJumpingHitting() {

}

void KickLeftJumpingHitting::update(MKCharacter *character, Events aEvent) {
    switch (aEvent) {
        case JumpFinished:
            character->setState(new CharacterStance());
        default:
            break;
    }
}

float KickLeftJumpingHitting::getWidth() {
    return 0;
}

string KickLeftJumpingHitting::getName() {
	return "KickLeftJumping";
}
