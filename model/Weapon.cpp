#include "Weapon.h"

Weapon::Weapon(float width, float height) {
    this->active = false;
    this->width = width;
    this->height = height;
}


Weapon::~Weapon() {
}

void Weapon::update() {
    if (this->isActive()) {
        this->stepForward();
    }
}

void Weapon::throwWeapon(float initialX, string direction) {
    if (!this->active) {
        this->active = true;
        this->positionX = initialX;
        this->direction = direction;
    }
}

void Weapon::stepForward() {
    if (this->direction == "Left")
        this->positionX += speed;
    else if (this->direction == "Right")
        this->positionX -= speed;
}

bool Weapon::isActive() {
    return this->active;
}

float Weapon::getPositionX() {
    return this->positionX;
}

void Weapon::destroy() {
    this->active = false;
}