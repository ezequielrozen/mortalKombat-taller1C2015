#include "Jumping.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"

Jumping::Jumping() {
}

Jumping::~Jumping() {
}

void Jumping::update(MKCharacter * character, Events aEvent) {
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

bool Jumping::isJumping() {
    return true;
}

string Jumping::getName() {
    return "Jumping";
}
