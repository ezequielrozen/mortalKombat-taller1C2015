//
// Created by mauri on 30/05/15.
//

#include "CharacterSelectionController.h"

CharacterSelectionController::CharacterSelectionController() {
	this->movingDownOne = false;
    this->movingUpOne = false;
    this->movingRightOne = false;
    this->movingLeftOne = false;
    this->movingDownTwo = false;
    this->movingUpTwo = false;
    this->movingRightTwo = false;
    this->movingLeftTwo = false;
}

CharacterSelectionController::~CharacterSelectionController() {

}

void CharacterSelectionController::update() {
}

void CharacterSelectionController::setCharacterSelection(CharacterSelection* characterSelection) {
	this->characterSelection = characterSelection;
}

void CharacterSelectionController::moveUp(int n) {
	if (n == 0) {
        if (!movingUpOne) {
            this->characterSelection->moveUp(n);
            this->movingUpOne = true;
        } 
    }
    else {
        if (!movingUpTwo) {
            this->characterSelection->moveUp(n);
            this->movingUpTwo = true;
        }
    }
}

void CharacterSelectionController::moveDown(int n) {
	if (n == 0) {
        if (!movingDownOne) {
            this->characterSelection->moveDown(n);
            this->movingDownOne = true;
        } 
    }
    else {
        if (!movingDownTwo) {
            this->characterSelection->moveDown(n);
            this->movingDownTwo = true;
        }
    }
}
void CharacterSelectionController::moveRight(int n) {
	if (n == 0) {
        if (!movingRightOne) {
            this->characterSelection->moveRight(n);
            this->movingRightOne = true;
        } 
    }
    else {
        if (!movingRightTwo) {
            this->characterSelection->moveRight(n);
            this->movingRightTwo = true;
        }
    }
}
void CharacterSelectionController::moveLeft(int n) {
	if (n == 0) {
        if (!movingLeftOne) {
            this->characterSelection->moveLeft(n);
            this->movingLeftOne = true;
        } 
    }
    else {
        if (!movingLeftTwo) {
            this->characterSelection->moveLeft(n);
            this->movingLeftTwo = true;
        }
    }
}
void CharacterSelectionController::moveRightRelease(int n) {
	if (n == 0) {
        this->movingRightOne = false;
    }
    else {
        this->movingRightTwo = false;
    }
}

void CharacterSelectionController::moveLeftRelease(int n) {
	if (n == 0) {
        this->movingLeftOne = false;
    }
    else {
        this->movingLeftTwo = false;
    }
}

void CharacterSelectionController::moveUpRelease(int n) {
	if (n == 0) {
        this->movingUpOne = false;
    }
    else {
        this->movingUpTwo = false;
    }
}

void CharacterSelectionController::moveDownRelease(int n) {
    if (n == 0) {
        this->movingDownOne = false;
    }
    else {
        this->movingDownTwo = false;
    }
}

void CharacterSelectionController::lowKick(int n) {
    if (n == 0) {
        this->characterSelection->select(n);
    }
    else {
        this->characterSelection->select(n);
    }
       // this->characterSelection->select(n);

}

void CharacterSelectionController::select() {
    this->characterSelection->mouseSelect();
}

void CharacterSelectionController::updateMousePosition(unsigned short x, unsigned short y) {
    this->characterSelection->updateMousePosition(x, y);
}