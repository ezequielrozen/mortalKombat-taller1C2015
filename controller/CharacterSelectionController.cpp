//
// Created by mauri on 30/05/15.
//

#include "CharacterSelectionController.h"

CharacterSelectionController::CharacterSelectionController() {
	this->movingDown = false;
    this->movingUp = false;
    this->movingRight = false;
    this->movingLeft = false;
}

CharacterSelectionController::~CharacterSelectionController() {

}

void CharacterSelectionController::update() {
}

void CharacterSelectionController::setCharacterSelection(CharacterSelection* characterSelection) {
	this->characterSelection = characterSelection;
}

void CharacterSelectionController::moveUp() {
	if (!movingUp) {
        this->characterSelection->moveUp();
        this->movingUp = true;
    }
}

void CharacterSelectionController::moveDown() {
	if (!movingDown) {
        this->characterSelection->moveDown();
        this->movingDown = true;
    }
}
void CharacterSelectionController::moveRight() {
	if (!movingRight) {
        this->characterSelection->moveRight();
        this->movingRight = true;
    }
}
void CharacterSelectionController::moveLeft() {
	if (!movingLeft) {
        this->characterSelection->moveLeft();
        this->movingLeft = true;
    }
}
void CharacterSelectionController::moveRightRelease() {
	this->movingRight = false;
}

void CharacterSelectionController::moveLeftRelease() {
	this->movingLeft = false;
}

void CharacterSelectionController::moveUpRelease() {
	this->movingUp = false;
}

void CharacterSelectionController::moveDownRelease() {
	this->movingDown = false;
}

void CharacterSelectionController::lowKick() {
    this->characterSelection->select();
}