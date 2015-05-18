#ifndef MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H
#define MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H

#include "../MKCharacter.h"
#include "CharacterState.h"
#include "MovingLeft.h"

class MovingRight : public CharacterState {

public:
    MovingRight();
    ~MovingRight();
    void update(MKCharacter * character, Events aEvent);
    bool isMovingRight();

    string getName();
    float getWidth();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H
