#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H

#include "Character.h"

class CharacterState {

public:
    virtual void update(Character*);

protected:
    void setState(Character*, CharacterState*);

};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H
