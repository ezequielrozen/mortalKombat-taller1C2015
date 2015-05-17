//
// Created by mauri on 17/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_JUMPING_H
#define MORTALKOMBAT_TALLER1C2015_JUMPING_H

#include "Character.h"
#include "CharacterState.h"

class Jumping : public CharacterState {


    public:
        Jumping();
        ~Jumping();
        void update(Character* character, Events aEvent );

    private:
        int timer;
    };


#endif //MORTALKOMBAT_TALLER1C2015_JUMPING_H
