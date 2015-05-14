#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTER_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTER_H

#include "CharacterState.h"

class Character {

public:
    Character();
    ~Character();

private:
    void update();

private:
    friend class CharacterState;
    void setState(CharacterState* state);

private:
    CharacterState* state;

};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTER_H
