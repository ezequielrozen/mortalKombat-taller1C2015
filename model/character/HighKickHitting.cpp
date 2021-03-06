#include "HighKickHitting.h"
#include "CharacterStance.h"
#include "ReceivingDuckingKick.h"
#include "KickLeftJumpingHitting.h"
#include "RecevingHit.h"
#include "ReceivingDuckingPunch.h"
#include "BeingOverPassedRight.h"
#include "BeingOverPassedLeft.h"
#include "TeleportationDoing.h"
#include "../../view/SoundManager.h"
#include "WeaponHittingIce.h"
#include "FatalityHitting.h"
#include "BeingPushed.h"

HighKickHitting::HighKickHitting() {
    this->timer = 40;
    SoundManager::getInstance()->playSound("hit2");
}

HighKickHitting::~HighKickHitting() {

}

void HighKickHitting::update(MKCharacter *character, Events aEvent) {
    switch(aEvent) {
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case OverPassed:
            if (character->getCharacterSide() == 'l') {
                character->setState(new BeingOverPassedLeft());
            } else {
                character->setState(new BeingOverPassedRight());
            };
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
        case ReceivingFlyHit:
            if (character->getName() == "scorpion") {
                character->setState(new BeingPushed());
            }
            break;
        default:
            break;
    }
    
}

float HighKickHitting::getWidth() {
    return 1.88;
}

string HighKickHitting::getName() {
    return "HighKickHitting";
}

void HighKickHitting::refreshTimer(MKCharacter* character) {

    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 40;
    }
    if (this->timer == 7) {
        cout << "IMPACT" << endl;
    }
    this->timer -= 1;
}

bool HighKickHitting::isHitting() {
    return true;
}

bool HighKickHitting::impact() {
    return (this->timer == 7);
}
