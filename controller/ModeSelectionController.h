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
    void moveUp();
    void moveDown();
    void moveUpRelease();
    void moveDownRelease();
    void lowKick();
private:
        ModeSelection* modeSelection;
        bool movingUp;
        bool movingDown;
};


#endif //MORTALKOMBAT_TALLER1C2015_MODESELECTIONCONTROLLER_H
