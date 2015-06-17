/*
 * FatalityHitting.cpp
 *
 *  Created on: 30/05/2015
 *      Author: her
 */

#include "FatalityHitting.h"
#include "CharacterStance.h"

FatalityHitting::FatalityHitting() {
	this->timer = 300;
	startThrow = false;

}

FatalityHitting::~FatalityHitting() {
}

string FatalityHitting::getName() {
    return "FatalityHitting";
}

void FatalityHitting::refreshTimer(MKCharacter* character) {

	if (this->timer == 240) {
		startThrow = true;
	}
	if (this->timer == 0) {
		character->setState(new CharacterStance());
	}

	this->timer -= 1;
}

bool FatalityHitting::startThrowingFire() {
	return this->startThrow;
}

float FatalityHitting::getWidth() {
    return 1.6;
}

float FatalityHitting::getHeight() {
    return 1.2;
}
