#include "HighPunchHitting.h"
#include "CharacterStance.h"
#include "ReceivingHit.h"
#include "ReceivingDuckingKick.h"

HighPunchHitting::HighPunchHitting() {
    this->timer = 40;
}

HighPunchHitting::~HighPunchHitting() {

}

void HighPunchHitting::update(MKCharacter *character, Events aEvent) {
    /*this->timer -= 1;
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 10;
    } else {*/
        switch (aEvent) {
            case LowKick:
                character->setState(new ReceivingHit());
                break;
            case DuckingKick:
                character->setState(new ReceivingDuckingKick());
                break;
            case HighKick:
                character->setState(new ReceivingHit());
                break;
            default:
                break;
        }
    
}

float HighPunchHitting::getWidth() {
    return 1.55;
}

string HighPunchHitting::getName() {
	return "HighPunchHitting";
}

void HighPunchHitting::refreshTimer(MKCharacter* character) {
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 40;
    }

    this->timer -= 1;
}

bool HighPunchHitting::isHitting() {
    return true;
}

bool HighPunchHitting::impact() {
    return (this->timer == 27);
}