#include "Weapon.h"

Weapon::Weapon(float width, float height) {
    this->active = false;
    this->width = width;
    this->height = height;
    this->speed = 3;
}


Weapon::~Weapon() {
}

void Weapon::update() {
    if (this->isActive()) {
        this->stepForward();
    }
}

void Weapon::throwWeapon(float initialX, float initialY, char direction) {
    if (!this->isActive()) {
        this->active = true;
        this->positionX = initialX;
        this->positionY = initialY;
        this->direction = direction;
    }
}

void Weapon::stepForward() {
	cout << positionX << endl;

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
}
