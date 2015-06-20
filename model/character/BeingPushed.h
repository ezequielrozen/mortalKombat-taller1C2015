//
// Created by her on 18/06/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_BEINGPUSHED_H
#define MORTALKOMBAT_TALLER1C2015_BEINGPUSHED_H


#include "CharacterState.h"

class BeingPushed: public CharacterState {
public:
    BeingPushed();
    virtual ~BeingPushed();
    string getName();
    //float getWidth();
    void refreshTimer(MKCharacter* character);
    void update(MKCharacter * character, Events aEvent);
    bool isMovingLeft();
    bool isMovingRight();
    void setTimer(int timer);
    void setMovingLeft(bool);
    void setMovingRight(bool);
private:
    int timer;
    bool movingRight;
    bool movingLeft;
};


#endif //MORTALKOMBAT_TALLER1C2015_BEINGPUSHED_H
