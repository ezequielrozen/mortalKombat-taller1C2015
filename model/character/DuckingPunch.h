#ifndef MORTALKOMBAT_TALLER1C2015_DUCKINGPUNCH_H
#define MORTALKOMBAT_TALLER1C2015_DUCKINGPUNCH_H


#include "CharacterState.h"

class DuckingPunch : public CharacterState {

public:
    DuckingPunch();

    ~DuckingPunch();

    virtual void update(MKCharacter *character, Events aEvent) override;

    virtual bool isMovingLeft() override;

    virtual bool isMovingRight() override;

    virtual bool isJumping() override;

    virtual bool isHitting() override;

    virtual bool isBlocking() override;

    virtual bool isDucking() override;

    virtual float getWidth() override;

    virtual string getName() override;

    virtual float getJumpLevel() override;

    virtual void refreshTimer(MKCharacter *character) override;

    virtual bool impact() override;

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_DUCKINGPUNCH_H
