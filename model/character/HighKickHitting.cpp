#include "HighKickHitting.h"
#include "CharacterStance.h"
#include "ReceivingDuckingKick.h"
#include "KickLeftJumpingHitting.h"
#include "RecevingHit.h"
#include "ReceivingDuckingPunch.h"
#include "BeingOverPassedRight.h"
#include "BeingOverPassedLeft.h"

HighKickHitting::HighKickHitting() {
    this->timer = 40;
}

HighKickHitting::~HighKickHitting() {

}

void HighKickHitting::update(MKCharacter *character, Events aEvent) {
    switch(aEvent) {
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case OverPassed:
            if (character->getCharacterSide() == 'l') {
                character->setState(new BeingOverPassedLeft());
            } else {
                character->setState(new BeingOverPassedRight());
            };
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
    return (this->timer == 7);
}
