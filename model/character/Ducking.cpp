#include "Ducking.h"
#include "CharacterStance.h"
#include "LowPunchHitting.h"
#include "DuckingKickHitting.h"
#include "RecevingHit.h"
#include "ReceivingDuckingKick.h"
#include "DuckingPunch.h"
#include "ReceivingDuckingPunch.h"
#include "BeingOverPassedRight.h"
#include "BeingOverPassedLeft.h"
#include "TeleportationDoing.h"
#include "WeaponHittingIce.h"
#include "FatalityHitting.h"

Ducking::Ducking() {
    this->timer = 10;
}

Ducking::~Ducking() {
}

void Ducking::update(MKCharacter * character, Events aEvent) {

    switch (aEvent) {
        case LowPunch:
            character->setState(new DuckingPunch());
            break;
        case HighKick:
            character->setState(new DuckingKickHitting());
            break;
        case ReceiveHit:
            character->setState(new ReceivingDuckingPunch());
            break;
        case DuckRelease:
            character->setState(new CharacterStance());
            break;
        case ReceiveDuckingKick:
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
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}

string Ducking::getName() {
    return "Ducking";
}

bool Ducking::isDucking() {
    return true;
}