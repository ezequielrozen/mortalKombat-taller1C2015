#include "WeaponHItting.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "RecevingHit.h"

WeaponHitting::WeaponHitting() {
	this->timer = 100;
}

WeaponHitting::~WeaponHitting() {

}

void WeaponHitting::update(MKCharacter* character, Events aEvent) {
	switch (aEvent) {
		case ReceiveWeapon:
			character->setState(new ReceivingDuckingPunch());
			break;
		case ReceiveHit:
			character->setState(new RecevingHit());
			break;
		default:
			//si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado

			break;

	}
}

string WeaponHitting::getName() {
	return "WeaponHitting";
}
   
float WeaponHitting::getWidth() {
	return 0;
}

void WeaponHitting::refreshTimer(MKCharacter* character) {

	if (this->timer == 0) {
		character->setState(new CharacterStance());
		cout << "stance " << endl;
		this->timer = 100;
	}

	this->timer -= 1;
}

bool WeaponHitting::startThrowing() {
	return this->timer == 85;
}
