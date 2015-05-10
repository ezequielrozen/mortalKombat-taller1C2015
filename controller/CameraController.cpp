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

bool CameraController::cameraMoveLeft(MKCharacter* character1, MKCharacter* character2) {
    return ((character1->getX() < Util::getInstance()->getLogicalWindowWidth()/10) && (character1->getMovement() == "LEFT")
        && !(character2->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character2->getWidth()));
}

bool CameraController::cameraMoveRight(MKCharacter* character1, MKCharacter* character2) {
    return ((character1->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character1->getWidth()) &&
        (character1->getMovement() == "RIGHT") && !(character2->getX() < Util::getInstance()->getLogicalWindowWidth()/10));
}

bool CameraController::update(MKCharacter* character1, MKCharacter* character2, std::list<Layer*>* layers) {
     extern logger* Mylog;

     bool cameraMoved;

    //cout << "posXchar1: " << character->getX() << endl;
    static double tempposx = 0;
    double posXchar1 = character1->getX();
    double posXchar2 = character2->getX();
    if(tempposx != posXchar1) {
        tempposx = posXchar1;
        extern logger* Mylog;
        char mensaje[200] = "Personaje se mueve respecto a pantalla. Nueva posicion: %1.2f";
        sprintf(mensaje, mensaje, posXchar1);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    }

    if ((this->cameraMoveLeft(character1, character2) && this->cameraMoveRight(character2, character1)) || 
        (this->cameraMoveLeft(character2, character1) && this->cameraMoveRight(character1, character2)) ||
        !(this->cameraMoveLeft(character1, character2) || this->cameraMoveRight(character1, character2) ||
         this->cameraMoveLeft(character2, character1) || this->cameraMoveRight(character2, character1))) {

        this->cameraMovement = "NONE";
        cameraMoved = false;
    }
    else if (this->cameraMoveLeft(character1, character2)) {
        this->cameraMovement = "LEFT";
        cameraMoved = true;
        character2->moveRight();
    }
    else if (this->cameraMoveLeft(character2, character1)) {
        this->cameraMovement = "LEFT";
        cameraMoved = true;
        character1->moveRight();
    }
    else if (this->cameraMoveRight(character1, character2)) {
        this->cameraMovement = "RIGHT";
        cameraMoved = true;
        character2->moveLeft();
    }
    else if (this->cameraMoveRight(character2, character1)) {
        this->cameraMovement = "RIGHT";
        cameraMoved = true;
        character1->moveLeft();
    }

    list<Layer*>::iterator it = layers->begin();
    for(it; it != layers->end(); it++) {
        (*it)->setMovement(cameraMovement);
    }
    for(it = layers->begin(); it != layers->end(); it++) {
    (*it)->update();
    }

    character1->UpdateJump();
    character2->UpdateJump();


    return cameraMoved;
}
