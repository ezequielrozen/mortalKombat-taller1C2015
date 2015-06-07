#ifndef MORTALKOMBAT_TALLER1C2015_WeaponIce_H
#define MORTALKOMBAT_TALLER1C2015_WeaponIce_H

#include <iostream>
#include "Throwable.h"

using namespace std;

class WeaponIce : public Throwable {
public:
    WeaponIce(float width, float height);
    ~WeaponIce();
    void update();
    bool isActive();
    void destroy();
    float getPositionX();
    float getPositionY();
    void throwWeapon(float initialPositionX, float initialPositionY, char direction);
    float getWidth();
    float getHeight();
    bool isImpact();

private:
    float speed;
    float positionX;
    float positionY;
    float height;
    float width;
    bool active;
    char direction;
    void stepForward();
    float traveledDistance;
    bool impact;

};


#endif //MORTALKOMBAT_TALLER1C2015_WeaponIce_H
