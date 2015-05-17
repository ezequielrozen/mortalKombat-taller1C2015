#ifndef MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H
#define MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H

#include "Character.h"
#include "CharacterState.h"

class MovingRight : public CharacterState {

public:
    MovingRight();
    ~MovingRight();
    void update(Character* character, Events aEvent);

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_MOVINGRIGHT_H
