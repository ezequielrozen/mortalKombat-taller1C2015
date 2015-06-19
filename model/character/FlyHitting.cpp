//
// Created by her on 16/06/15.
//

#include "FlyHitting.h"
#include "CharacterStance.h"

FlyHitting::FlyHitting() {
    this->timer = 120;
    this->sideWhenInit=' ';
    this->checkSide = true;
}

FlyHitting::~FlyHitting() {
    this->sideWhenInit=' ';
    this->checkSide = true;
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
    }

    if (this->timer == 0) {
        character->setState(new CharacterStance());
        this->sideWhenInit=' ';
        this->checkSide = true;
        this->timer = 120;
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
    return true;
}

bool FlyHitting::isMovingRight() {
    return false;
}