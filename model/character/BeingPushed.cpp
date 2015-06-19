//
// Created by her on 18/06/15.
//

#include "BeingPushed.h"
#include "CharacterStance.h"

BeingPushed::BeingPushed() {
    this->timer = 100;
}

BeingPushed::~BeingPushed() {
}

void BeingPushed::update(MKCharacter * character, Events aEvent) {


}
string BeingPushed::getName() {
    return "BeingPushed";
}

void BeingPushed::refreshTimer(MKCharacter* character) {

    if (this->timer == 0) {
        character->setState(new CharacterStance());
//		cout << "stance " << endl;
        this->timer = 100;
    }

    this->timer -= 1;
}

bool BeingPushed::isMovingLeft() {
    return true;
}