//
// Created by her on 18/06/15.
//

#include "BeingPushed.h"
#include "CharacterStance.h"
#include "../../view/SoundManager.h"


BeingPushed::BeingPushed() {
    this->timer = 3;
    this->setMovingRight(false);
    this->setMovingLeft(false);
    this->movingLeft = false;
    this->movingRight = false;
    SoundManager::getInstance()->playSound("receivehit");
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
        this->timer = 3;
    }

    this->timer -= 1;
}
void BeingPushed::setTimer(int time){
    //Para q lo setee solo una vez.
    if (this->timer == 3)
        this->timer = time;
}

bool BeingPushed::isMovingLeft() {
    return this->movingLeft;
}

bool BeingPushed::isMovingRight(){
    return this->movingRight;
}

void BeingPushed::setMovingLeft(bool state){
    this->movingLeft = state;
}
void BeingPushed::setMovingRight(bool state){
    this->movingRight = state;
}