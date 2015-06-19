#include "Jumping.h"
#include <iostream>
#include "CharacterStance.h"
#include "MovingRight.h"
#include "MovingLeft.h"
#include "Ducking.h"
#include "HighPunchHitting.h"
#include "LowPunchHitting.h"
#include "HighKickHitting.h"
#include "Blocking.h"
#include "WeaponHItting.h"
#include "RecevingHit.h"
#include "LowKickHitting.h"
#include "ReceivingDuckingPunch.h"
#include "ReceivingDuckingKick.h"
#include "BeingOverPassedLeft.h"
#include "BeingOverPassedRight.h"
#include "FatalityHitting.h"
#include "TeleportationDoing.h"
#include "WeaponHittingIce.h"
#include "ReceivingIce.h"
#include "FlyHitting.h"
#include "ReceivingFire.h"
#include "BeingPushed.h"

CharacterStance::CharacterStance() {
//    this->timer = -1
}

CharacterStance::~CharacterStance() {

}

void CharacterStance::update(MKCharacter * character, Events aEvent) {

//    std::cout << "Update desde StanceState." << std::endl;

    switch (aEvent) {
        case MoveRight:
            character->setState(new MovingRight());
            break;
        case MoveLeft:
            character->setState(new MovingLeft());
            break;
        case Jump:
            character->setState(new Jumping());
            break;
        case Duck:
            character->setState(new Ducking());
            break;
        case HighPunch:
            character->setState(new HighPunchHitting());
            break;
        case LowPunch:
            character->setState(new LowPunchHitting());
            break;
        case HighKick:
            character->setState(new HighKickHitting());
            break;
        case LowKick:
            character->setState(new LowKickHitting());
            break;
        case Block:
            character->setState(new Blocking());
            break;
        case WeaponHit:
			character->setState(new WeaponHitting());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case FatalityHit:
        	if (character->getFatalityEnable())
        		character->setState(new FatalityHitting());
            break;
        case Teleportation:
        		character->setState(new TeleportationDoing());
            break;
        case WeaponHitIce:
            if (character->getName() == "raiden"){
			    character->setState(new WeaponHittingIce());
            }
            break;
        case OverPassed:
            if (character->getCharacterSide() == 'l') {
                character->setState(new BeingOverPassedLeft());
            } else {
                character->setState(new BeingOverPassedRight());
            };
            break;
        case ReceiveIce:
            character->setState(new ReceivingIce());
            break;
        case FlyHit:
            if (character->getName() == "raiden") {
                character->setState(new FlyHitting());
            }
            break;
        case ReceivingFlyHit:
            if (character->getName() == "raiden") {
                character->setState(new BeingPushed());
            }
            break;
        case ReceiveFire:
            character->setState(new ReceivingFire());
            break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado

            break;

    }
}

string CharacterStance::getName() {
    return "Stance";
}
