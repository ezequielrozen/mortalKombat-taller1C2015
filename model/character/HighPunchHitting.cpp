#include "HighPunchHitting.h"
#include "CharacterStance.h"
#include "ReceivingHit.h"
#include "ReceivingDuckingKick.h"

HighPunchHitting::HighPunchHitting() {
    this->timer = 10;
}

HighPunchHitting::~HighPunchHitting() {

}

void HighPunchHitting::update(MKCharacter *character, Events aEvent) {
    this->timer -= 1;
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 10;
    } else {
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
}

float HighPunchHitting::getWidth() {
    return 0;
}

string HighPunchHitting::getName() {
	return "HighPunchHitting";
}