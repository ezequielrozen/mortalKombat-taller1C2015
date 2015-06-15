//
// Created by mauri on 29/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSELECTIONCONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSELECTIONCONTROLLER_H


#include "MKStageController.h"
#include "../model/CharacterSelection.h"

class CharacterSelectionController : public MKStageController {
public:
    CharacterSelectionController();
    ~CharacterSelectionController();
    void update();
    void setCharacterSelection(CharacterSelection* characterSelection);
    void moveUp(int n);
    void moveDown(int n);
    void moveRight(int n);
    void moveLeft(int n);
    void moveRightRelease(int n);
    void moveLeftRelease(int n);
    void moveUpRelease(int n);
    void moveDownRelease(int n);
    void lowKick(int n);

    void select();
    void updateMousePosition(unsigned short x, unsigned short y);

    void updateName(string letter);
private:
	CharacterSelection* characterSelection;
	bool movingUpOne;
	bool movingDownOne;
	bool movingRightOne;
	bool movingLeftOne;
    bool movingUpTwo;
    bool movingDownTwo;
    bool movingRightTwo;
    bool movingLeftTwo;
};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSELECTIONCONTROLLER_H
