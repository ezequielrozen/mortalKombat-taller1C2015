#ifndef MORTALKOMBAT_TALLER1C2015_JumpingRight_H
#define MORTALKOMBAT_TALLER1C2015_JumpingRight_H

#include "../MKCharacter.h"
#include "CharacterState.h"
#include "PunchRightJumping.h"

class JumpingRight : public CharacterState {


public:
    JumpingRight();
    ~JumpingRight();
    void update(MKCharacter * character, Events aEvent );
    bool isJumping();
    bool isMovingRight();
    string getName();

private:
    float getHeight();
};


#endif //MORTALKOMBAT_TALLER1C2015_JumpingRight_H
