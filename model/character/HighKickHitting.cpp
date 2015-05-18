#include "HighKickHitting.h"
#include "CharacterStance.h"
#include "ReceivingHit.h"
#include "ReceivingDuckingKick.h"
#include "KickLeftJumpingHitting.h"

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
            case DuckingKick:
                character->setState(new ReceivingDuckingKick());
                break;
            case LowKick:
                character->setState(new ReceivingHit());
                break;
            case JumpingKickLeft:
                character->setState(new ReceivingHit());
                break;
            case JumpingKickRight:
                character->setState(new ReceivingHit());
                break;
            default:
                break;
        }
    }
}

float HighKickHitting::getWidth() {
    return 0;
}

string HighKickHitting::getName() {
    return "HighKickHitting";
}