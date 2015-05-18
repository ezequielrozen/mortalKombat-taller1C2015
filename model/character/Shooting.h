#ifndef MORTALKOMBAT_TALLER1C2015_SHOOTING_H
#define MORTALKOMBAT_TALLER1C2015_SHOOTING_H

#include "../MKCharacter.h"

class Shooting : public CharacterState {

public:
    Shooting();
    ~Shooting();
    void update(MKCharacter * character, Events aEvent );

    string getName();
    float getWidth();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_SHOOTING_H
