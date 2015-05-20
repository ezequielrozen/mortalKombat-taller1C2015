#include "JumpingRight.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"

JumpingRight::JumpingRight() {
}

JumpingRight::~JumpingRight() {
}

void JumpingRight::update(MKCharacter * character, Events aEvent) {
    switch (aEvent) {
        case ReceiveHit:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
        case JumpFinished:
            character->setState(new CharacterStance());
        default:
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
