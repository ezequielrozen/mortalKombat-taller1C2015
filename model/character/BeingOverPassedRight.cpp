//
// Created by mauri on 24/05/15.
//

#include "BeingOverPassedRight.h"
#include "JumpingRight.h"
#include "RecevingHit.h"
#include "ReceivingDuckingKick.h"


BeingOverPassedRight::BeingOverPassedRight() {
//    this->timer =
}

BeingOverPassedRight::~BeingOverPassedRight() {
}

void BeingOverPassedRight::update(MKCharacter * character, Events aEvent) {
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

        default:
            break;
    }

}

bool BeingOverPassedRight::isMovingRight() {
    return true;
}

string BeingOverPassedRight::getName() {
    return "MovingRight";
}

bool BeingOverPassedRight::isBeingOverPassedRight() {
    return true;
}