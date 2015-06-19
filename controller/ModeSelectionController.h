//
// Created by mauri on 29/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_MODESELECTIONCONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_MODESELECTIONCONTROLLER_H


#include "MKStageController.h"
#include "../model/ModeSelection.h"

class ModeSelectionController : public MKStageController {
public:
    ModeSelectionController();
    ~ModeSelectionController();
    void setModeSelection(ModeSelection* modeSelection);
    void update();
    void moveUp(int n);
    void moveDown(int n);
    void moveUpRelease(int n);
    void moveDownRelease(int n);
    void lowKick(int n);
    void select();
    void updateMousePosition(unsigned short x, unsigned short y);
    void updateName(string letter);

    void moveRight(int n);
    void moveLeft(int n);
    void highKick(int n);
    void highPunch(int n);
    void lowPunch(int n);
private:
        ModeSelection* modeSelection;
        bool movingUp;
        bool movingDown;
};


#endif //MORTALKOMBAT_TALLER1C2015_MODESELECTIONCONTROLLER_H
