#include "Blocking.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "TeleportationDoing.h"
#include "FatalityHitting.h"
#include "BeingPushed.h"

Blocking::Blocking() {

}

Blocking::~Blocking() {

}

void Blocking::update(MKCharacter *character, Events aEvent) {
    switch(aEvent) {
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case BlockRelease:
            character->setState(new CharacterStance());
            break;
        case Teleportation:
            character->setState(new TeleportationDoing());
            break;
        case FatalityHit:
            if (character->getFatalityEnable())
                character->setState(new FatalityHitting());
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

string Blocking::getName() {
	return "Blocking";
}

bool Blocking::isBlocking() {
	return true;
}