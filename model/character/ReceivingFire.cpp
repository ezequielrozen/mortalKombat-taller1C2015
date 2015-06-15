#include "ReceivingFire.h"
#include "../../view/SoundManager.h"

ReceivingFire::ReceivingFire() {
	this->timer = 80;
	//SoundManager::getInstance()->playSound("burn");
}

ReceivingFire::~ReceivingFire() {
}

string ReceivingFire::getName() {
	return "ReceivingFire";
}

float ReceivingFire::getWidth() {
	return 1.37;
}


