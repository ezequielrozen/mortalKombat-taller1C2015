#include "HighKickHitting.h"
#include "../MKCharacter.h"
#include "CharacterStance.h"
#include "ReceivingHighPunch.h"

HighKickHitting::HighKickHitting() {
    this->timer = 10;
}

HighKickHitting::~HighKickHitting() {

}

void HighKickHitting::update(MKCharacter *character, Events aEvent) {
    this->timer -= 1;
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        //restart timer.
        this->timer = 10;
    } else {
        switch(aEvent) {
            case HighPunch:
                character->setState(new ReceivingHighPunch());
                break;
            default:
                break;
        }
    }
}

float HighKickHitting::getWidth() {
    return 0;
}
