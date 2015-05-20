#include "Blocking.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"

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