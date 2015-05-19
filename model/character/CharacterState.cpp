#include "CharacterState.h"
#include "../MKCharacter.h"
void CharacterState::update(MKCharacter *character, Events anEvent) {

}

void CharacterState::setState(MKCharacter *character, CharacterState *state) {
    character->setState(state);
}

bool CharacterState::isMovingLeft() {
	return false;
}

bool CharacterState::isMovingRight() {
	return false;
}

bool CharacterState::isJumping() {
	return false;
}

bool CharacterState::isHitting() {
	return false;
}

bool CharacterState::isBlocking() {
	return false;
}

bool CharacterState::isDucking() {
	return false;
}

float CharacterState::getWidth() {
	return 1;
}

string CharacterState::getName() {
	return "asd";
}

void CharacterState::refreshTimer(MKCharacter* character) {
	
}

bool CharacterState::impact() {
	return false;
}