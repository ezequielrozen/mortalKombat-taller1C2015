#include "WeaponIce.h"
#include "util/Util.h"

WeaponIce::WeaponIce(float width, float height) {
    this->active = false;
    this->width = width;
    this->height = height;
    this->speed = 5;
}


WeaponIce::~WeaponIce() {
}

void WeaponIce::update() {
    if (this->isActive()) {
        this->stepForward();
        if (this->traveledDistance > Util::getInstance()->getLogicalWindowWidth()) {
            this->destroy();
        } else {
            this->traveledDistance+= this->speed;
        }
    }
}


void WeaponIce::throwWeapon(float initialX, float initialY, char direction) {
    if (!this->isActive()) {
        this->traveledDistance = 0;
        this->active = true;
        this->positionX = initialX;
        this->positionY = initialY;
        this->direction = direction;
        this->impact = true;
    }
}

void WeaponIce::stepForward() {

	if (this->direction == 'r')
        this->positionX -= speed;
    else if (this->direction == 'l')
        this->positionX += speed;
}

bool WeaponIce::isActive() {
    return this->active;
}

float WeaponIce::getPositionX() {
    return this->positionX;
}

void WeaponIce::destroy() {
    this->active = false;
    this->impact = false;
}

float WeaponIce::getWidth() {
    return this->width;
}

float WeaponIce::getHeight() {
    return this->height;
}

float WeaponIce::getPositionY() {
    return this->positionY;
}

bool WeaponIce::isImpact() {
    return this->impact;
}

