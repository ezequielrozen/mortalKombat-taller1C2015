#ifndef MORTALKOMBAT_TALLER1C2015_JUMPING_H
#define MORTALKOMBAT_TALLER1C2015_JUMPING_H

#include "../MKCharacter.h"
#include "CharacterState.h"

class Jumping : public CharacterState {


    public:
        Jumping();
        ~Jumping();
        void update(MKCharacter * character, Events aEvent );
    	bool isJumping();

    	string getName();
    	float getWidth();

    private:
        int timer;
    };


#endif //MORTALKOMBAT_TALLER1C2015_JUMPING_H
