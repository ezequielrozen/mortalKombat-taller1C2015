#include "CameraController.h"
#include "../model/util/Util.h"
#include "../model/logger.h"

CameraController::CameraController()
{

    this->cameraMovement = "NONE";
}


CameraController::~CameraController(void)
{
}

bool CameraController::update(MKCharacter* character, MKCharacter* character2, std::list<Layer*>* layers) {
     extern logger* Mylog;

     bool cameraMoved;

    //cout << "posXchar1: " << character->getX() << endl;
    static double tempposx = 0;
    double posXchar1 = character->getX();
    double posXchar2 = character2->getX();
    if(tempposx != posXchar1) {
        tempposx = posXchar1;
        extern logger* Mylog;
        char mensaje[200] = "Personaje se mueve respecto a pantalla. Nueva posicion: %1.2f";
        sprintf(mensaje, mensaje, posXchar1);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    }

    if ((character->getX() < Util::getInstance()->getLogicalWindowWidth()) && (character->getMovement() == "LEFT")) {
        this->cameraMovement = "LEFT";
        cameraMoved = true;
    }
    else if ((character->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character->getWidth()) &&
            (character->getMovement() == "RIGHT")) {
        this->cameraMovement = "RIGHT";
        cameraMoved = true;
    }

    if ((character2->getX() < Util::getInstance()->getLogicalWindowWidth()/10) && (character2->getMovement() == "LEFT")) {
        this->cameraMovement = "LEFT";
        cameraMoved = true;
    } else if ((character2->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character2->getWidth()) &&
             (character2->getMovement() == "RIGHT")) {
        this->cameraMovement = "RIGHT";
        cameraMoved = true;
    } else {
        this->cameraMovement = "NONE";
        cameraMoved = false;
    }

    list<Layer*>::iterator it = layers->begin();
    for(it; it != layers->end(); it++) {
        (*it)->setMovement(cameraMovement);
    }
    for(it = layers->begin(); it != layers->end(); it++) {
    (*it)->update();
    }

    character->UpdateJump();
    character2->UpdateJump();

    return cameraMoved;
}
