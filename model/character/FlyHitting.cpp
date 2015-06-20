//
// Created by her on 16/06/15.
//

#include "FlyHitting.h"
#include "CharacterStance.h"

FlyHitting::FlyHitting() {
    this->timer = 60;
    this->sideWhenInit=' ';
    this->checkSide = true;
    this->movingLeft = false;
    this->movingRight = false;
}

FlyHitting::~FlyHitting() {
    this->sideWhenInit=' ';
    this->checkSide = true;
    this->setMovingRight(false);
    this->setMovingLeft(false);
}
bool FlyHitting::impact() {
    return true;
}
string FlyHitting::getName() {
    return "FlyHitting";
}

bool FlyHitting::isHitting()
{
    return true;
}
void FlyHitting::refreshTimer(MKCharacter* character) {

    if (this->sideWhenInit ==' ')
    {
        this->sideWhenInit = character->getCharacterSide();
        if (this->sideWhenInit == 'r') {
            this->setMovingLeft(true);
            this->setMovingRight(false);
        }
        if (this->sideWhenInit == 'l') {
            this->setMovingLeft(false);
            this->setMovingRight(true);
        }
    }

    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->sideWhenInit=' ';
        this->checkSide = true;
        this->timer = 60;
    }
    this->timer -= 1;
}

float FlyHitting::getWidth() {
    return 1.6;
}

float FlyHitting::getHeight() {
    return 1.2;
}
char FlyHitting::getSideWhenInit()
{
    return this->sideWhenInit;
}

bool FlyHitting::isMovingLeft() {
    return this->movingLeft;
}

bool FlyHitting::isMovingRight() {
    return this->movingRight;
}

int FlyHitting::getTimer(){
    return this->timer;
}

void FlyHitting::setMovingLeft(bool state){
    this->movingLeft = state;
}
void FlyHitting::setMovingRight(bool state){
    this->movingRight = state;
}