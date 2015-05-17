#include "CharacterState.h"

void CharacterState::update(Character *character, Events anEvent) {

}

void CharacterState::setState(Character *character, CharacterState *state) {
    character->setState(state);
}
