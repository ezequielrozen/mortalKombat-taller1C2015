/*
 * Fire.h
 *
 *  Created on: 30/05/2015
 *      Author: her
 */

#ifndef FIRE_H_
#define FIRE_H_

#include "Throwable.h"
#include <iostream>

class Fire: public Throwable {
public:
    Fire(float width, float height);
    ~Fire();
    void update();
    bool isActive();
    void destroy();
    float getPositionX();
    float getPositionY();
    void throwWeapon(float initialPositionX, float initialPositionY, char direction);
    float getWidth();
    float getHeight();
    bool isImpact();
    int getCurrentWeaponIce();

private:
    float speed;
    float positionX;
    float positionY;
    float height;
    float width;
    bool active;
    char direction;
    void stepForward();
    bool impact;
    int currentUpdate;
};

#endif /* FIRE_H_ */
