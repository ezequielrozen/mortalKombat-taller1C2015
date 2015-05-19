#include "DuckingKickHitting.h"
#include "CharacterStance.h"

DuckingKickHitting::DuckingKickHitting() {
    this->timer = 27;
}

DuckingKickHitting::~DuckingKickHitting() {

}

void DuckingKickHitting::update(MKCharacter *character, Events aEvent) {   
        
}

string DuckingKickHitting::getName() {
    return "DuckingKickHitting";
}

float DuckingKickHitting::getWidth() {
    return 1.79;
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
        this->timer = 27;
    }

    this->timer -= 1;
}

bool DuckingKickHitting::impact() {
    return (this->timer == 20);
}