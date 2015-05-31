//
// Created by mauri on 29/05/15.
//

#include "ModeSelectionController.h"

ModeSelectionController::ModeSelectionController() {
    // acá debería recibir el ModeSelection (modelo) para actualizarlo
    this->movingDown = false;
    this->movingUp = false;
}

ModeSelectionController::~ModeSelectionController() {

}

void ModeSelectionController::update() {

}

void ModeSelectionController::moveUp() {
    if (!movingUp) {
        this->modeSelection->moveUp();
        this->movingUp = true;
    }
}

void ModeSelectionController::moveDown() {
    if (!movingDown) {
        this->modeSelection->moveDown();
        this->movingDown = true;
    }
}


void ModeSelectionController::setModeSelection(ModeSelection* modeSelection) {
    this->modeSelection = modeSelection;
}

void ModeSelectionController::lowKick() {
    this->modeSelection->select();
}

void ModeSelectionController::moveUpRelease() {
    this->movingUp = false;
}

void ModeSelectionController::moveDownRelease() {
    this->movingDown = false;
}
