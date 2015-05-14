#include "CharacterState.h"

void CharacterState::update(Character *character) {}

void CharacterState::setState(Character *character, CharacterState *state) {
    character->setState(state);
}
