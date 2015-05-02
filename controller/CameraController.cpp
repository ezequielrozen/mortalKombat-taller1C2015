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

bool CameraController::update(MKCharacter* character, std::list<Layer*>* layers) {
     extern logger* Mylog;

     bool cameraMoved;

    //cout << "posX: " << character->getX() << endl;
    static double tempposx = 0;
    double posX = character->getX();
    if(tempposx != posX){
        tempposx = posX;
        extern logger* Mylog;
        char mensaje[200] = "Personaje se mueve respecto a pantalla. Nueva posicion: %1.2f";
        sprintf(mensaje, mensaje, posX);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    }

    if ((character->getX() < Util::getInstance()->getLogicalWindowWidth()/10) && (character->getMovement() == "LEFT")) {
        this->cameraMovement = "LEFT";
        cameraMoved = true;
    }
    else if ((character->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character->getWidth()) &&
            (character->getMovement() == "RIGHT")) {
        this->cameraMovement = "RIGHT";
        cameraMoved = true;
    }
    else {
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

    return cameraMoved;
}
