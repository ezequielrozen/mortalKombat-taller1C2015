//
// Created by mauri on 18/05/15.
//

#include "ReceivingDuckingPunch.h"
#include "CharacterStance.h"

ReceivingDuckingPunch::ReceivingDuckingPunch() {

}

ReceivingDuckingPunch::~ReceivingDuckingPunch() {

}

void ReceivingDuckingPunch::update(MKCharacter *character, Events aEvent) {
	 switch (aEvent) {
        case JumpFinished:
            character->setState(new CharacterStance());
            break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;
    }
}

string ReceivingDuckingPunch::getName() {
    return "ReceivingDuckingPunch";
}

bool ReceivingDuckingPunch::isJumping() {
	return true;
}

float ReceivingDuckingPunch::getJumpLevel() {
	return 0.6;
}

float ReceivingDuckingPunch::getWidth() {
	return 1.83;
}

bool ReceivingDuckingPunch::isReceivingHit() {
    return true;
}