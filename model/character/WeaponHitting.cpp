#include "WeaponHItting.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "RecevingHit.h"
#include "../../view/SoundManager.h"
#include "WeaponHittingIce.h"
#include "TeleportationDoing.h"
#include "FatalityHitting.h"

WeaponHitting::WeaponHitting() {
	this->timer = 1;
	SoundManager::getInstance()->playSound("weapon");
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
		case Teleportation:
			character->setState(new TeleportationDoing());
			break;
		case WeaponHitIce:
			if (character->getName() == "raiden"){
				character->setState(new WeaponHittingIce());
			}
			break;
		case FatalityHit:
			if (character->getFatalityEnable())
				character->setState(new FatalityHitting());
			break;
		default:
			//si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado

			break;

	}
}

string WeaponHitting::getName() {
	return "WeaponHitting";
}

void WeaponHitting::refreshTimer(MKCharacter* character) {

	if (this->timer == 0) {
		character->setState(new CharacterStance());
//		cout << "stance " << endl;
		this->timer = 1;
	}

	this->timer -= 1;
}

bool WeaponHitting::startThrowing() {
	return true;
}
