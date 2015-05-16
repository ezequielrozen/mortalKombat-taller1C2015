#include "CharacterState.h"

void CharacterState::update(Character *character, MKEvent* anEvent) {

}

void CharacterState::setState(Character *character, CharacterState *state) {
    character->setState(state);
}

void CharacterState::getState() { }