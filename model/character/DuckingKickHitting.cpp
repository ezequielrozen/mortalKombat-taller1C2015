#include "DuckingKickHitting.h"
#include "CharacterStance.h"
#include "RecevingHit.h"
#include "BeingOverPassedRight.h"
#include "BeingOverPassedLeft.h"

DuckingKickHitting::DuckingKickHitting() {
    this->timer = 33;
}

DuckingKickHitting::~DuckingKickHitting() {

}

void DuckingKickHitting::update(MKCharacter *character, Events aEvent) {   
    switch(aEvent) {
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

string DuckingKickHitting::getName() {
    return "DuckingKickHitting";
}

float DuckingKickHitting::getWidth() {
    return 1.79;
}

float DuckingKickHitting::getHeight() {
    return 0.3;
}

bool DuckingKickHitting::isDucking() {
    return true;
}

bool DuckingKickHitting::isHitting() {
    return true;
}

void DuckingKickHitting::refreshTimer(MKCharacter* character) {

    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 33;
    }

    this->timer -= 1;
}

bool DuckingKickHitting::impact() {
    return (this->timer == 7);
}