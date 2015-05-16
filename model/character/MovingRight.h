//
// Created by mauri on 14/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H
#define MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H

#include "Character.h"
#include "CharacterState.h"

class MovingRight : public CharacterState {
    public:
        MovingRight();
        ~MovingRight();
        void update(Character* character, MKEvent* aEvent);
        void getState();
};


#endif //MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H
