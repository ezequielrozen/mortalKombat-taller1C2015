#include "ReceivingFire.h"
#include "../../view/SoundManager.h"
#include "CharacterStance.h"

ReceivingFire::ReceivingFire() {
	this->timer = 400;
	SoundManager::getInstance()->playSound("burn");
}

ReceivingFire::~ReceivingFire() {
}

string ReceivingFire::getName() {
	return "ReceivingFire";
}

float ReceivingFire::getWidth() {
	return 1.37;
}
void ReceivingFire::refreshTimer(MKCharacter* character) {
	if (this->timer == 0) {
		character->setState(new CharacterStance());
	}

	this->timer -= 1;
}


