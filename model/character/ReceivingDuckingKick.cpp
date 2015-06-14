#include "ReceivingDuckingKick.h"
#include "CharacterStance.h"
#include "../../view/SoundManager.h"

ReceivingDuckingKick::ReceivingDuckingKick() {
    this->timer = 30;
    SoundManager::getInstance()->playSound("fall");
}

ReceivingDuckingKick::~ReceivingDuckingKick() {

}

void ReceivingDuckingKick::update(MKCharacter *character, Events aEvent) {

}

string ReceivingDuckingKick::getName() {
    return "ReceivingDuckingKick";
}

float ReceivingDuckingKick::getWidth() {
    return 0;
}

void ReceivingDuckingKick::refreshTimer(MKCharacter* character) {
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 30;
    }

    this->timer -= 1;
}

bool ReceivingDuckingKick::isReceivingHit() {
	return true;
}