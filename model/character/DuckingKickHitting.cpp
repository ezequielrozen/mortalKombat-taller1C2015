#include "DuckingKickHitting.h"
#include "CharacterStance.h"

DuckingKickHitting::DuckingKickHitting() {
    this->timer = 10;
}

DuckingKickHitting::~DuckingKickHitting() {

}

void DuckingKickHitting::update(MKCharacter *character, Events aEvent) {
    this->timer -= 1;
    if (this->timer == 0) {
        character->setState(new CharacterStance());
    } else {
        switch (aEvent) {
            default:
                break;
        }
    }
}

float DuckingKickHitting::getWidth() {
    return 0;
}
