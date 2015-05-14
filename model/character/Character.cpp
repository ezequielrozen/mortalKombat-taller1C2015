#include "Character.h"
#include "CharacterStance.h"

Character::Character() {
    this->state = new CharacterStance();
}

Character::~Character() {

}

void Character::update() {
    this->state->update(this);
}

void Character::setState(CharacterState* state) {

}
