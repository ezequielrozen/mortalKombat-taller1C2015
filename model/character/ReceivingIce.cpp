//
// Created by her on 14/06/15.
//
#include "ReceivingIce.h"
#include "Jumping.h"
#include "CharacterStance.h"
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
#include "TeleportationDoing.h"
#include "WeaponHittingIce.h"


ReceivingIce::ReceivingIce() {
    this->timer = 400;
    //SoundManager::getInstance()->playSound("burn");
}

ReceivingIce::~ReceivingIce() {
}

void ReceivingIce::update(MKCharacter * character, Events aEvent) {

    switch (aEvent) {
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
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado

            break;

    }
}
string ReceivingIce::getName() {
    return "ReceivingIce";
}

void ReceivingIce::refreshTimer(MKCharacter* character) {

    if (this->timer == 0) {
        character->setState(new CharacterStance());
//		cout << "stance " << endl;
        this->timer = 30;
    }

    this->timer -= 1;
}

//float ReceivingIce::getWidth() {
//    return 1.37;
//}
