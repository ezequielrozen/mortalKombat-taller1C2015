
#include "Character.h"
#include "CharacterStance.h"

Character::Character() {
    this->state = new CharacterStance();
}

Character::~Character() {

}

void Character::update(MKEvent* aEvent) {
    this->state->update(this, aEvent);
}

void Character::setState(CharacterState *state) {
    this->state = state;
}

