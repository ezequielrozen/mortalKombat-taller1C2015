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
    return ((character1->getX() < 4) && (character1->isMovingLeft())
        && !(character2->getX() > Util::getInstance()->getLogicalWindowWidth() - 4 - character2->getWidth()));
}

bool CameraController::cameraMoveRight(MKCharacter* character1, MKCharacter* character2) {
    return ((character1->getX() > Util::getInstance()->getLogicalWindowWidth() - 4 - character1->getWidth()) &&
        (character1->isMovingRight() && !(character2->getX() < 4)));
}

/*
bool CameraController::cameraMoveLeft(MKCharacter* character1, MKCharacter* character2) {
    return ((character1->getX() < Util::getInstance()->getLogicalWindowWidth()/10) && (character1->getMovement() == "LEFT")
        && !(character2->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character2->getWidth()));
}

bool CameraController::cameraMoveRight(MKCharacter* character1, MKCharacter* character2) {
    return ((character1->getX() > Util::getInstance()->getLogicalWindowWidth() - Util::getInstance()->getLogicalWindowWidth()/10 - character1->getWidth()) &&
        (character1->getMovement() == "RIGHT") && !(character2->getX() < Util::getInstance()->getLogicalWindowWidth()/10));
}
*/

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
        if (character1->getStagePosX() > 0) {
            character2->moveRight();
            character1->decreaseStagePosX();
            character2->decreaseStagePosX();
        }
        else {
            cameraMoved = false;
        }
    }
    else if (this->cameraMoveLeft(character2, character1)) {
        this->cameraMovement = "LEFT";
        cameraMoved = true;
        if (character2->getStagePosX() > 0) {
            character1->moveRight();
            character2->decreaseStagePosX();
            character1->decreaseStagePosX();
        }
        else {
            cameraMoved = false;
        }
    }
    else if (this->cameraMoveRight(character1, character2)) {
        this->cameraMovement = "RIGHT";
        cameraMoved = true;
        if (character1->getStagePosX() < (Util::getInstance()->getLogicalStageWidth()-character1->getWidth())) {
            character2->moveLeft();
            character1->increaseStagePosX();
            character2->increaseStagePosX();
        }
        else {
            cameraMoved = false;
        }
    }
    else if (this->cameraMoveRight(character2, character1)) {
        this->cameraMovement = "RIGHT";
        cameraMoved = true;
        if (character2->getStagePosX() < (Util::getInstance()->getLogicalStageWidth()-character2->getWidth())) {
            character1->moveLeft();
            character2->increaseStagePosX();
            character1->increaseStagePosX();
        }
        else {
            cameraMoved = false;
        }
    }

    list<Layer*>::iterator it = layers->begin();
    for(it; it != layers->end(); it++) {
        (*it)->setMovement(cameraMovement);
    }
    for(it = layers->begin(); it != layers->end(); it++) {
    (*it)->update();
    }


    return cameraMoved;
}
