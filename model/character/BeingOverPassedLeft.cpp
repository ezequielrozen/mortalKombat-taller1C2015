//
// Created by mauri on 24/05/15.
//

#include "BeingOverPassedLeft.h"
#include "RecevingHit.h"
#include "ReceivingDuckingKick.h"
#include "ReceivingDuckingPunch.h"
#include "CharacterStance.h"


BeingOverPassedLeft::BeingOverPassedLeft() {
//    this->timer =
}

BeingOverPassedLeft::~BeingOverPassedLeft() {
}

void BeingOverPassedLeft::update(MKCharacter * character, Events aEvent) {
    switch (aEvent) {
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case ReceiveDuckingKick:
            character->setState(new ReceivingDuckingKick());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case OverPassedFinished:
            character->setState(new CharacterStance());
            break;
        default:
            break;
    }

}

bool BeingOverPassedLeft::isMovingLeft() {
    return true;
}

string BeingOverPassedLeft::getName() {
    return "MovingLeft";
}

bool BeingOverPassedLeft::isBeingOverPassedLeft() {
    return true;
}