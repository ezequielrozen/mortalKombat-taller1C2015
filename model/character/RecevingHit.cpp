#include "RecevingHit.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "../../view/SoundManager.h"

RecevingHit::RecevingHit() {
	this->timer = 23;
	SoundManager::getInstance()->playSound("receivehit");
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

bool RecevingHit::isReceivingHit() {
	return true;
}
