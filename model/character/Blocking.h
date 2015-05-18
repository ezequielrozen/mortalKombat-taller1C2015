#ifndef MORTALKOMBAT_TALLER1C2015_BLOCKING_H
#define MORTALKOMBAT_TALLER1C2015_BLOCKING_H


#include "../MKCharacter.h"

class Blocking : public CharacterState {

public:
    Blocking();
    virtual ~Blocking();
    void update(MKCharacter * character, Events aEvent );

    string getName();
    float getWidth();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_BLOCKING_H
