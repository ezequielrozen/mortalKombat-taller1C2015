#include "HighKickHitting.h"
#include "CharacterStance.h"
#include "ReceivingHit.h"
#include "ReceivingDuckingKick.h"
#include "KickLeftJumpingHitting.h"

HighKickHitting::HighKickHitting() {
    this->timer = 40;
}

HighKickHitting::~HighKickHitting() {

}

void HighKickHitting::update(MKCharacter *character, Events aEvent) {
    /*this->timer -= 1;
    cout << this->timer << endl;
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        //restart timer.
        this->timer = 10;
    } else {*/

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

float HighKickHitting::getWidth() {
    return 1.88;
}

string HighKickHitting::getName() {
    return "HighKickHitting";
}

void HighKickHitting::refreshTimer(MKCharacter* character) {

    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 40;
    }

    this->timer -= 1;
}

bool HighKickHitting::isHitting() {
    return true;
}

bool HighKickHitting::impact() {
    return (this->timer == 14);
}
