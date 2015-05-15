#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTER_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTER_H

#include "CharacterState.h"

class Character {
friend class CharacterState;

public:
    Character();
    ~Character();

private:
    void update();
   // void setState(CharacterState* state, Event* aEvent);
//   CharacterState* state;

};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTER_H
