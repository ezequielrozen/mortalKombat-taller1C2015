#ifndef MORTALKOMBAT_TALLER1C2015_JumpingLeft_H
#define MORTALKOMBAT_TALLER1C2015_JumpingLeft_H

#include "../MKCharacter.h"
#include "CharacterState.h"

class JumpingLeft : public CharacterState {


public:
    JumpingLeft();
    ~JumpingLeft();
    void update(MKCharacter * character, Events aEvent );
    bool isJumping();
    bool isMovingLeft();
    string getName();

private:
    float getHeight();
};


#endif //MORTALKOMBAT_TALLER1C2015_JumpingLeft_H
