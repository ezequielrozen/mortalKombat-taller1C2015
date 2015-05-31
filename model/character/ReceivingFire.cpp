#include "ReceivingFire.h"

ReceivingFire::ReceivingFire() {
	this->timer = 99999999;

}

ReceivingFire::~ReceivingFire() {
}

string ReceivingFire::getName() {
	return "ReceivingFire";
}

float ReceivingFire::getWidth() {
	return 1.37;
}


