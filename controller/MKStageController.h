//
// Created by mauri on 29/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_MKSTAGECONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_MKSTAGECONTROLLER_H
#include "../model/MKCharacter.h"

class ModeSelection;

class MKStageController {
public:
    virtual void update() {};
    virtual void moveRight() {};
    virtual void moveLeft() {};
    virtual void moveUp() {};
    virtual void moveDown() {};
    virtual void highKick() {};
    virtual void lowKick() {};
    virtual void highPunch() {};
    virtual void lowPunch() {};
    virtual void shoot() {};
    virtual void block() {};
    virtual void duckPunch() {};

    virtual void moveLeftRelease() {};
    virtual void moveRightRelease() {};
    virtual void moveDownRelease() {};
    virtual void moveUpRelease() {};
    virtual void blockRelease() {};

    virtual void setCharacterToMove(MKCharacter* character) {};
    virtual void setModeSelection(ModeSelection* modeSelection) {};
};


#endif //MORTALKOMBAT_TALLER1C2015_MKSTAGECONTROLLER_H
