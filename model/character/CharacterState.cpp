#include "CharacterState.h"
#include "../MKCharacter.h"
void CharacterState::update(MKCharacter *character, Events anEvent) {

}

void CharacterState::setState(MKCharacter *character, CharacterState *state) {
    character->setState(state);
}
