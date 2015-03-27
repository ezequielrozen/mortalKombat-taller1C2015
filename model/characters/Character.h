#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTER_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTER_H

#include "../movables/Position.h"

class Character {

public:
    Character(float x, float y);
    ~Character();
    void setPositionX(float);
    void setPositionY(float);
    float getPositionX();
    float getPositionY();

private:
    Position* position;
};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTER_H
