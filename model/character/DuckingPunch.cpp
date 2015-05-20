#include "DuckingPunch.h"
#include "ReceivingDuckingKick.h"
#include "RecevingHit.h"
#include "ReceivingDuckingPunch.h"

DuckingPunch::DuckingPunch() {
    this->timer = 10;
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
    return CharacterState::isHitting();
}

bool DuckingPunch::isBlocking() {
    return CharacterState::isBlocking();
}

bool DuckingPunch::isDucking() {
    return CharacterState::isDucking();
}

float DuckingPunch::getWidth() {
    return 1.51;
}

string DuckingPunch::getName() {
    return "DuckingPunch";
}

float DuckingPunch::getJumpLevel() {
    return CharacterState::getJumpLevel();
}

void DuckingPunch::refreshTimer(MKCharacter *character) {
    CharacterState::refreshTimer(character);
}

bool DuckingPunch::impact() {
    return CharacterState::impact();
}

