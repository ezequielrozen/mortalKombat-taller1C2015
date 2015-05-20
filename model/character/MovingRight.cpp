#include "MovingRight.h"
#include "CharacterStance.h"
#include "JumpingRight.h"
#include "LowPunchHitting.h"
#include "LowKickHitting.h"
#include "RecevingHit.h"
#include "ReceivingDuckingKick.h"
#include "HighKickHitting.h"
#include "HighPunchHitting.h"
#include "WeaponHItting.h"
#include "Ducking.h"

MovingRight::MovingRight() {
//    this->timer =
}

MovingRight::~MovingRight() {
}

void MovingRight::update(MKCharacter * character, Events aEvent) {
    switch (aEvent) {
        case Jump:
            character->setState(new JumpingRight());
            break;
        case Duck:
            character->setState(new Ducking());
            break;
        case HighKick:
            character->setState(new HighKickHitting());
            break;
        case HighPunch:
            character->setState(new HighPunchHitting());
            break;
        case LowPunch:
            character->setState(new LowPunchHitting());
            break;
        case LowKick:
            character->setState(new LowKickHitting());
            break;
        case WeaponHit:
            if (!character->getWeapon()->isActive()) {
                character->setState(new WeaponHitting());
            }
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case MoveLeft:
            character->setState(new MovingLeft());
            break;
        case MoveRightRelease:
            character->setState(new CharacterStance());
            break;
        default:
            break;
    }
}

bool MovingRight::isMovingRight() {
    return true;
}

string MovingRight::getName() {
    return "MovingRight";
}
