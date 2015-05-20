//
// Created by mauri on 20/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_WEAPON_H
#define MORTALKOMBAT_TALLER1C2015_WEAPON_H

#include <iostream>

using namespace std;

class Weapon {
public:
    Weapon();
    ~Weapon();
private:
    float speed;
    float height;
    float width;
    string direction;
};


#endif //MORTALKOMBAT_TALLER1C2015_WEAPON_H
