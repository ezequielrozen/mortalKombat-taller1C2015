/*
#include "MKCharacter.h"
#include "CharacterStance.h"

MKCharacter::MKCharacter() {
    this->state = new CharacterStance();
}

MKCharacter::~MKCharacter() {
    delete this->state;
}

void MKCharacter::setState(CharacterState *state) {
    delete this->state;
    this->state = state;
}

void MKCharacter::update(Events aEvent) {
    this->state->update(this, aEvent);
}
*/
