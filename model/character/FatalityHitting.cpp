/*
 * FatalityHitting.cpp
 *
 *  Created on: 30/05/2015
 *      Author: her
 */

#include "FatalityHitting.h"
#include "CharacterStance.h"

FatalityHitting::FatalityHitting() {
	this->timer = 60;

}

FatalityHitting::~FatalityHitting() {
}

string FatalityHitting::getName() {
    return "FatalityHitting";
}

void FatalityHitting::refreshTimer(MKCharacter* character) {

//	if (this->timer == 0) {
//		character->setState(new CharacterStance());
////		cout << "stance " << endl;
//		this->timer = 60;
//	}
//
//	this->timer -= 1;
}

bool FatalityHitting::startThrowing() {
	return false;
}

float FatalityHitting::getWidth() {
    return 1.6;
}

float FatalityHitting::getHeight() {
    return 1.2;
}
