#include "Blocking.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"

Blocking::Blocking() {

}

Blocking::~Blocking() {

}

void Blocking::update(MKCharacter *character, Events aEvent) {
    switch(aEvent) {
        case BlockRelease:
            character->setState(new CharacterStance());
            break;
        default:
            break;
    }
}
