#include "DuckingPunch.h"
#include "ReceivingDuckingKick.h"
#include "RecevingHit.h"
#include "ReceivingDuckingPunch.h"
#include "CharacterStance.h"
#include "BeingOverPassedLeft.h"
#include "BeingOverPassedRight.h"
#include "TeleportationDoing.h"
#include "../../view/SoundManager.h"
#include "WeaponHittingIce.h"
#include "FatalityHitting.h"
#include "WeaponHItting.h"

DuckingPunch::DuckingPunch() {
    this->timer = 33;
    SoundManager::getInstance()->playSound("getoverhere");

}

DuckingPunch::~DuckingPunch() {

}

void DuckingPunch::update(MKCharacter *character, Events aEvent) {
    switch(aEvent) {
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case ReceiveDuckingPunch:
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
        case WeaponHit:
            character->setState(new WeaponHitting());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
        default:
            break;
    }
}

bool DuckingPunch::isMovingLeft() {
    return CharacterState::isMovingLeft();
}

bool DuckingPunch::isMovingRight() {
    return CharacterState::isMovingRight();
}

bool DuckingPunch::isJumping() {
    return CharacterState::isJumping();
}

bool DuckingPunch::isHitting() {
    return true;
}

bool DuckingPunch::isBlocking() {
    return CharacterState::isBlocking();
}

bool DuckingPunch::isDucking() {
    return true;
}

float DuckingPunch::getWidth() {
    return 1.51;
}

string DuckingPunch::getName() {
    return "DuckingPunch";
}

float DuckingPunch::getJumpLevel() {
    return 0.6;
}

void DuckingPunch::refreshTimer(MKCharacter *character) {
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 33;
    }

    this->timer -= 1;
}

bool DuckingPunch::impact() {
    return this->timer == 7;
}
