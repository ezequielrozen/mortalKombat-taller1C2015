/*
 * Fire.cpp
 *
 *  Created on: 30/05/2015
 *      Author: her
 */

#include "Fire.h"
#include "util/Util.h"

Fire::Fire(float width, float height) {
    this->active = false;
    this->width = width;
    this->height = height;
    this->speed = 1;
    this->impact = false;
}

Fire::~Fire() {

}


void Fire::update() {
if (this->isActive()) {
	this->stepForward();
	int posHit = 330;
	cout << this->positionY << endl;
	if (this->positionY > posHit && this->positionY < posHit+3) {
		this->impact = true;
	}
	if (this->positionY >= posHit+3){
		this->destroy();
	}
//        } else {
//            this->traveledDistance+= this->speed;
	}
}



void Fire::throwWeapon(float initialX, float initialY, char direction) {
    if (!this->isActive()) {
//        this->traveledDistance = 0;
        this->active = true;
        this->positionX = initialX;
        this->positionY = initialY;
        this->direction = direction;
    }
}

void Fire::stepForward() {
	if (this->direction == 'r'){
        this->positionX -= speed*1.5;
        this->positionY += speed;
	}
    else if (this->direction == 'l'){
        this->positionX += speed*1.5;
        this->positionY += speed;
    }
}

bool Fire::isActive() {
    return this->active;
}

float Fire::getPositionX() {
    return this->positionX;
}

void Fire::destroy() {
    this->active = false;
    this->impact = false;
}

float Fire::getWidth() {
    return this->width;
}

float Fire::getHeight() {
    return this->height;
}

float Fire::getPositionY() {
    return this->positionY;
}

bool Fire::isImpact() {
    return this->impact;
}

