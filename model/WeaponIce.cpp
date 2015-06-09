#include "WeaponIce.h"
#include "util/Util.h"

WeaponIce::WeaponIce(float width, float height) {
    this->active = false;
    this->width = width;
    this->height = height;
    this->speed = 5;
    this->currentUpdate = 0;
    this->impactingWeaponIce = false;
}


WeaponIce::~WeaponIce() {
}

void WeaponIce::update() {
    if (this->isActive()) {

    	this->stepForward();

    	this->currentUpdate ++;

        if (this->traveledDistance > Util::getInstance()->getLogicalWindowWidth()) {
            this->destroy();
        } else {
            this->traveledDistance+= this->speed;
        }
    }else
    {
    	if (this->currentUpdate > 30)
    	{
    		this->setImpactingWeaponIce(false);
    	}
    	this->currentUpdate ++;
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
        this->impactingWeaponIce = false;
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
    this->currentUpdate = 0;
    cout << "destroy" << endl;
}

void WeaponIce::setImpactingWeaponIce(bool value){
	this->impactingWeaponIce = value;
}
bool WeaponIce::getImpactingWeaponIce(){
	return this->impactingWeaponIce;
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

bool WeaponIce::isStarting()
{
	return (this->currentUpdate <= 1);
}

