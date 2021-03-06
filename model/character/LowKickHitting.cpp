#include "LowKickHitting.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingDuckingKick.h"
#include "RecevingHit.h"
#include "ReceivingDuckingPunch.h"
#include "BeingOverPassedRight.h"
#include "BeingOverPassedLeft.h"
#include "TeleportationDoing.h"
#include "../../view/SoundManager.h"
#include "WeaponHittingIce.h"
#include "FatalityHitting.h"

LowKickHitting::LowKickHitting() {
    this->timer = 40;
    SoundManager::getInstance()->playSound("hit2");

}

LowKickHitting::~LowKickHitting() {

}

void LowKickHitting::update(MKCharacter* character, Events aEvent) {
    switch (aEvent) {
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case OverPassed:
            if (character->getCharacterSide() == 'l') {
                character->setState(new BeingOverPassedLeft());
            } else {
                character->setState(new BeingOverPassedRight());
            };
            break;
        case Teleportation:
            character->setState(new TeleportationDoing());
            break;
        case WeaponHitIce:
            if (character->getName() == "raiden"){
                character->setState(new WeaponHittingIce());
            }
            break;
        case FatalityHit:
            if (character->getFatalityEnable())
                character->setState(new FatalityHitting());
            break;
        default:
            break;
    }
}

float LowKickHitting::getWidth() {
    return 1.88;
}

void LowKickHitting::refreshTimer(MKCharacter* character) {

    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 40;
    }

    this->timer -= 1;
}

bool LowKickHitting::isHitting() {
    return true;
}

string LowKickHitting::getName() {
	return "LowKickHitting";
}

bool LowKickHitting::impact() {
    return (this->timer == 7);
}
