#include "Weapon.h"
#include "util/Util.h"

Weapon::Weapon(float width, float height) {
    this->active = false;
    this->width = width;
    this->height = height;
    this->speed = 5;
}


Weapon::~Weapon() {
}

void Weapon::update() {
    if (this->isActive()) {
        this->stepForward();
        if (this->traveledDistance > Util::getInstance()->getLogicalWindowWidth()) {
            this->destroy();
        } else {
            this->traveledDistance+= this->speed;
        }
    }
}


void Weapon::throwWeapon(float initialX, float initialY, char direction) {
    if (!this->isActive()) {
        this->traveledDistance = 0;
        this->active = true;
        this->positionX = initialX;
        this->positionY = initialY;
        this->direction = direction;
        this->impact = true;
    }
}

void Weapon::stepForward() {

	if (this->direction == 'r')
        this->positionX -= speed;
    else if (this->direction == 'l')
        this->positionX += speed;
}

bool Weapon::isActive() {
    return this->active;
}

float Weapon::getPositionX() {
    return this->positionX;
}

void Weapon::destroy() {
    this->active = false;
    this->impact = false;
}

float Weapon::getWidth() {
    return this->width;
}

float Weapon::getHeight() {
    return this->height;
}

float Weapon::getPositionY() {
    return this->positionY;
}

bool Weapon::isImpact() {
    return this->impact;
}

