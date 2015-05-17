#ifndef MORTALKOMBAT_TALLER1C2015_BLOCKING_H
#define MORTALKOMBAT_TALLER1C2015_BLOCKING_H


#include "Character.h"

class Blocking : public CharacterState {

public:
    Blocking();
    ~Blocking();
    void update(Character* character, Events aEvent );

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_BLOCKING_H
