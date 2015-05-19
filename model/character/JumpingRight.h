#ifndef MORTALKOMBAT_TALLER1C2015_JumpingRight_H
#define MORTALKOMBAT_TALLER1C2015_JumpingRight_H

#include "../MKCharacter.h"
#include "CharacterState.h"

class JumpingRight : public CharacterState {


public:
    JumpingRight();
    ~JumpingRight();
    void update(MKCharacter * character, Events aEvent );
    bool isJumping();
    bool isMovingRight();
    string getName();
    float getWidth();

private:
};


#endif //MORTALKOMBAT_TALLER1C2015_JumpingRight_H
