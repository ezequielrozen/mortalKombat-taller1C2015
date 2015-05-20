#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H

#include "../MKCharacter.h"
#include "../constantes.h"
#include <map>
class MKCharacter;

class CharacterState {

public:
    virtual void update(MKCharacter * character, Events aEvent );
    virtual bool isMovingLeft();
    virtual bool isMovingRight();
    virtual bool isJumping();
    virtual bool isHitting();
    virtual bool isBlocking();
    virtual bool isDucking();
    virtual float getWidth();
    virtual string getName();
    virtual float getJumpLevel();
    virtual void refreshTimer(MKCharacter* character);
    virtual bool startThrowing();

    virtual bool impact();

protected:
    virtual void setState(MKCharacter * character, CharacterState* aState);
    map<Events, CharacterState>* eventMap;

};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSTATE_H

