#include "JumpingRight.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "WeaponHItting.h"
#include "MovingRight.h"

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
            break;
        case JumpFinished:
            character->setState(new CharacterStance());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case WeaponHit:
            if (!character->getWeapon()->isActive()) {
                character->setState(new WeaponHitting());
            }
            break;
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
