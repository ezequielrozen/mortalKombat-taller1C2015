#include "WeaponHItting.h"
#include "../MKCharacter.h"

WeaponHitting::WeaponHitting() {
	this->timer = 10;
}

void WeaponHitting::refreshTimer(MKCharacter *character) {

}

WeaponHitting::~WeaponHitting() {

}

void WeaponHitting::update(MKCharacter* character, Events aEvent) {

}

string WeaponHitting::getName() {
	return "WeaponHitting";
}
   
float WeaponHitting::getWidth() {
	return 0;
}