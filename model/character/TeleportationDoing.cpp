/*
 * TeleportationDoing.cpp
 *
 *  Created on: 05/06/2015
 *      Author: her
 */

#include "TeleportationDoing.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "RecevingHit.h"

TeleportationDoing::TeleportationDoing() {
	// TODO Auto-generated constructor stub
	this->finalPosX = 0;
	this->timer=60;
}

TeleportationDoing::~TeleportationDoing() {
	// TODO Auto-generated destructor stub
}

string TeleportationDoing::getName() {
    return "TeleportationDoing";
}

void TeleportationDoing::update(MKCharacter* character, Events aEvent) {
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

void TeleportationDoing::refreshTimer(MKCharacter* character) {
	if (this->timer == 20) {
		character->setX(this->finalPosX);
	}
	if (this->timer == 0) {
		character->setState(new CharacterStance());
		this->timer = 1;
	}

	this->timer -= 1;
}

void TeleportationDoing::setFinalPosX(float finalX)
{
	this->finalPosX = finalX;
}

float TeleportationDoing::getFinalPosX()
{
	return this->finalPosX;
}
