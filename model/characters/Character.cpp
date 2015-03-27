#include "Character.h"

Character::Character(float x, float y) {
    this->position = new Position(x, y);
}

Character::~Character() {
    delete(this->position);
}

void Character::setPositionX(float x) {
    this->position->setCoordinateX(x);
}

void Character::setPositionY(float y) {
    this->position->setCoordinateY(y);
}

float Character::getPositionY() {
    return this->position->getCoordinateY();
}

float Character::getPositionX() {
    return this->position->getCoordinateX();
}
