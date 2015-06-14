#include "ReceivingBlow.h"
#include "../../view/SoundManager.h"

ReceivingBlow::ReceivingBlow() {
	SoundManager::getInstance()->playSound("receivehit");
}

ReceivingBlow::~ReceivingBlow() {

}

void ReceivingBlow::update(MKCharacter *character, Events aEvent) {

}

string ReceivingBlow::getName() {
	return "ReceivingBlow";
}

float ReceivingBlow::getWidth() {
	return 0;
}