#ifndef MORTALKOMBAT_TALLER1C2015_MOVINGLEFT_H
#define MORTALKOMBAT_TALLER1C2015_MOVINGLEFT_H

#include "../MKCharacter.h"
#include "CharacterState.h"

class MovingLeft : public CharacterState {

public:
    MovingLeft();
    ~MovingLeft();
    void update(MKCharacter * character, Events aEvent );
    bool isMovingLeft();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_MOVINGLEFT_H

