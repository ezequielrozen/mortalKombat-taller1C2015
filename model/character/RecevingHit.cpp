#include "RecevingHit.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"

RecevingHit::RecevingHit() {
	this->timer = 23;
}

RecevingHit::~RecevingHit() {

}

void RecevingHit::update(MKCharacter *character, Events aEvent) {

}

string RecevingHit::getName() {
	return "RecevingHit";
}

float RecevingHit::getWidth() {
	return 1.37;
}

void RecevingHit::refreshTimer(MKCharacter* character) {
	if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 23;
    }

    this->timer -= 1;
}

