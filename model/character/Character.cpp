#include "Character.h"
#include "CharacterStance.h"

Character::Character() {
    this->state = new CharacterStance();
}

Character::~Character() {
    delete this->state;
}

void Character::setState(CharacterState *state) {
    delete this->state;
    this->state = state;
}

void Character::update(Events aEvent) {
    this->state->update(this, aEvent);
}
