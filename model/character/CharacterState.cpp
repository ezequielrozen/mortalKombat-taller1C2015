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

float CharacterState::getWidth() {
	return 0;
}
