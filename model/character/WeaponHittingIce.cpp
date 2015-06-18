#include "WeaponHittingIce.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "RecevingHit.h"
#include "../../view/SoundManager.h"

WeaponHittingIce::WeaponHittingIce() {
	this->timer = 20;
	SoundManager::getInstance()->playSound("ray");
}

WeaponHittingIce::~WeaponHittingIce() {

}

void WeaponHittingIce::update(MKCharacter* character, Events aEvent) {
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

string WeaponHittingIce::getName() {
	return "WeaponHittingIce";
}

void WeaponHittingIce::refreshTimer(MKCharacter* character) {

	if (this->timer == 0) {
		character->setState(new CharacterStance());
//		cout << "stance " << endl;
		this->timer = 1;
	}

	this->timer -= 1;
}

bool WeaponHittingIce::startThrowing() {
	return true;
}
