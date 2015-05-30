//
// Created by mauri on 29/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_MODESELECTIONCONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_MODESELECTIONCONTROLLER_H


#include "MKStageController.h"

class ModeSelectionController : public MKStageController {
public:
    ModeSelectionController();
    ~ModeSelectionController();
    void update();
    void moveRight();
};


#endif //MORTALKOMBAT_TALLER1C2015_MODESELECTIONCONTROLLER_H
