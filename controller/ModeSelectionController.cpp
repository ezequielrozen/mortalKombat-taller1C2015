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

void ModeSelectionController::moveUp(int n) {
    if (!movingUp && n == 0) {
        this->modeSelection->moveUp();
        this->movingUp = true;
    }
}

void ModeSelectionController::moveDown(int n) {
    if (!movingDown && n == 0) {
        this->modeSelection->moveDown();
        this->movingDown = true;
        cout << "MOVE DOWN" << endl;
    }
}


void ModeSelectionController::setModeSelection(ModeSelection* modeSelection) {
    this->modeSelection = modeSelection;
}

void ModeSelectionController::lowKick(int n) {
    if (n == 0) {
        this->modeSelection->select();
    }
}

void ModeSelectionController::moveUpRelease(int n) {
    if (n == 0) {
        this->movingUp = false;
    }
}

void ModeSelectionController::moveDownRelease(int n) {
    if (n == 0) {
        this->movingDown = false;
    }
}

void ModeSelectionController::select() {
    this->modeSelection->mouseSelect();
}

void ModeSelectionController::updateMousePosition(unsigned short x, unsigned short y) {
    this->modeSelection->updateMousePosition(x, y);
}
