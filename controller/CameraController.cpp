#include "CameraController.h"
#include "../model/util/Util.h"

CameraController::CameraController()
{

    this->cameraMovement = "NONE";
}


CameraController::~CameraController(void)
{
}

void CameraController::update(MKCharacter* character, std::list<Layer*>* layers) {
    
    //cout << "posX: " << character->getX() << endl;

    if ((character->getX() < Util::getInstance()->getLogicalWindowWidth()/10) && (character->getMovement() == "LEFT")) {
        this->cameraMovement = "LEFT";
    }
    else if ((character->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character->getWidth()) &&
            (character->getMovement() == "RIGHT")) {
        this->cameraMovement = "RIGHT";
    }
    else {
        this->cameraMovement = "NONE";
        character->Update();
    }

    list<Layer*>::iterator it = layers->begin();
    for(it; it != layers->end(); it++) {
        (*it)->setMovement(cameraMovement);
    }
    for(it = layers->begin(); it != layers->end(); it++) {
    (*it)->update();
    }

    character->UpdateJump();
}
