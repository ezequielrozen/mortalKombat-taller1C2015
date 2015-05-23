#include "DuckingPunch.h"
#include "ReceivingDuckingKick.h"
#include "RecevingHit.h"
#include "ReceivingDuckingPunch.h"
#include "CharacterStance.h"

DuckingPunch::DuckingPunch() {
    this->timer = 33;
}

DuckingPunch::~DuckingPunch() {

}

void DuckingPunch::update(MKCharacter *character, Events aEvent) {
    switch(aEvent) {
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        default:
            break;
    }
}

bool DuckingPunch::isMovingLeft() {
    return CharacterState::isMovingLeft();
}

bool DuckingPunch::isMovingRight() {
    return CharacterState::isMovingRight();
}

bool DuckingPunch::isJumping() {
    return CharacterState::isJumping();
}

bool DuckingPunch::isHitting() {
    return true;
}

bool DuckingPunch::isBlocking() {
    return CharacterState::isBlocking();
}

bool DuckingPunch::isDucking() {
    return true;
}

float DuckingPunch::getWidth() {
    return 1.51;
}

string DuckingPunch::getName() {
    return "DuckingPunch";
}

float DuckingPunch::getJumpLevel() {
    return 0.6;
}

void DuckingPunch::refreshTimer(MKCharacter *character) {
    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->timer = 33;
    }

    this->timer -= 1;
}

bool DuckingPunch::impact() {
    return this->timer == 7;
}
