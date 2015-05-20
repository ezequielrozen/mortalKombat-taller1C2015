//
// Created by mauri on 20/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_WEAPON_H
#define MORTALKOMBAT_TALLER1C2015_WEAPON_H

#include <iostream>

using namespace std;

class Weapon {
public:
    Weapon(float width, float height);
    ~Weapon();
    void update();
    bool isActive();
    void destroy();
    float getPositionX();
    void throwWeapon(float initialPositionX, float initialPositionY, char direction);
    float getWidth();
    float getHeight();
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
};


#endif //MORTALKOMBAT_TALLER1C2015_WEAPON_H
