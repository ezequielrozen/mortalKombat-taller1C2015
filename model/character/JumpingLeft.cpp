#include "JumpingLeft.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "PunchLeftJumping.h"

JumpingLeft::JumpingLeft() {
}

JumpingLeft::~JumpingLeft() {
}

void JumpingLeft::update(MKCharacter * character, Events aEvent) {
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

bool JumpingLeft::isJumping() {
    return true;
}

string JumpingLeft::getName() {
    return "JumpingLeft";
}

bool JumpingLeft::isMovingLeft() {
    return true;
}
