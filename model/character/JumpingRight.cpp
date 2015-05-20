#include "JumpingRight.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "WeaponHItting.h"
#include "MovingRight.h"
#include "PunchLeftJumping.h"
#include "KickRightJumpingHitting.h"

JumpingRight::JumpingRight() {
}

JumpingRight::~JumpingRight() {
}

void JumpingRight::update(MKCharacter * character, Events aEvent) {
    switch (aEvent) {
        case HighPunch:
            character->setState(new PunchRightJumping());
            break;
        case LowPunch:
            character->setState(new PunchRightJumping());
            break;
        case HighKick:
            character->setState(new KickRightJumpingHitting());
            break;
        case LowKick:
            character->setState(new KickRightJumpingHitting());
            break;
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
