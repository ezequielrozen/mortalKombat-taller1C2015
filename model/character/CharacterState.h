#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H

#include "Character.h"
#include "../MKEvents/MoveLeft.h"
#include "../MKEvents/MoveRight.h"
#include "../constantes.h"
#include <map>
class Character;

enum Events { MoveRight, MoveLeft, Jump, Duck};


class CharacterState {

public:
    virtual void update(Character* character, MKEvent* aEvent );
    virtual void getState();

protected:
    void setState(Character* character, CharacterState* aState);
    map<Events, CharacterState> eventMap;
};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H

