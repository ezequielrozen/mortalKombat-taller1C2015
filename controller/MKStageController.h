//
// Created by mauri on 29/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_MKSTAGECONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_MKSTAGECONTROLLER_H
#include "../model/MKCharacter.h"

class ModeSelection;
class CharacterSelection;
class InputController;

class MKStageController {
public:
    virtual void update() {};
    virtual void moveRight(int n) {};
    virtual void moveLeft(int n) {};
    virtual void moveUp(int n) {};
    virtual void moveDown(int n) {};
    virtual void highKick() {};
    virtual void lowKick(int n) {};
    virtual void highPunch() {};
    virtual void lowPunch() {};
    virtual void shoot() {};
    virtual void block() {};
    virtual void duckPunch() {};
    virtual void select() {};
    virtual void updateMousePosition(unsigned short x, unsigned short y) {};

    virtual void moveLeftRelease(int n) {};
    virtual void moveRightRelease(int n) {};
    virtual void moveDownRelease(int n) {};
    virtual void moveUpRelease(int n) {};
    virtual void lowKickRelease(int n) {};
    virtual void highKickRelease(int n) {};
    virtual void lowPunchRelease(int n) {};
    virtual void highPunchRelease(int n) {};
    virtual void blockRelease() {};
    virtual void weaponRelease() {};

    virtual void setCharacterToMove(MKCharacter* character) {};
    virtual void setModeSelection(ModeSelection* modeSelection) {};
    virtual void setCharacterSelection(CharacterSelection* characterSelection) {};
};


#endif //MORTALKOMBAT_TALLER1C2015_MKSTAGECONTROLLER_H
