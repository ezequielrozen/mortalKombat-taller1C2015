#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H

#include "Character.h"
#include "../constantes.h"
#include <map>
class Character;

class CharacterState {

public:
    virtual void update(Character* character, Events aEvent );
    virtual void getState();

protected:
    void setState(Character* character, CharacterState* aState);
    map<Events, CharacterState>* eventMap;

};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H

