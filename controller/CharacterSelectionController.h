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
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveRightRelease();
    void moveLeftRelease();
    void moveUpRelease();
    void moveDownRelease();
    void lowKick();
private:
	CharacterSelection* characterSelection;
	bool movingUp;
	bool movingDown;
	bool movingRight;
	bool movingLeft;
};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSELECTIONCONTROLLER_H
