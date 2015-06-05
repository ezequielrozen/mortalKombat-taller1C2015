#include "CharacterSelection.h"

CharacterSelection::CharacterSelection(SDL_Renderer* renderer, InputController* inputController) {
	
	this->inputController = inputController;

	this->buttons.push_back(new Button("character", true));
	for (int i = 1; i < 12; i++) {
		this->buttons.push_back(new Button("character", false));
	}

	this->view = new CharacterSelectionView(renderer, this->buttons);

	this->actualButton = 0;
	this->lastButton = 1;

	this->buttonPressed = false;
}

CharacterSelection::~CharacterSelection() {
	delete view;
}

void CharacterSelection::linkInputController() {
	this->inputController->setCharacterSelection(this);
}

void CharacterSelection::moveUp() {
	this->lastButton = actualButton;

	if (this->actualButton > 3) {
		this->actualButton = actualButton - 4;
	}
	else {
		this->actualButton = actualButton + 8;
	}
}

void CharacterSelection::moveDown() {
	this->lastButton = actualButton;
	
	if (this->actualButton < 8) {
		this->actualButton = actualButton + 4;
	}
	else {
		this->actualButton = actualButton - 8;
	}
}

void CharacterSelection::moveRight() {
	this->lastButton = actualButton;

	if (this->actualButton < 11) {
		this->actualButton++;
	}
	else {
		this->actualButton = 0;
	}
}

void CharacterSelection::moveLeft() {
	this->lastButton = actualButton;

	if (this->actualButton > 0) {
		this->actualButton--;
	}
	else {
		this->actualButton = 11;
	}
}

void CharacterSelection::select() {
	this->buttonPressed = true;
}

void CharacterSelection::loop() {
	
	while ( inputController->getEvent()->type != SDL_QUIT && !(this->buttonPressed)) {
		inputController->checkEvent();
		inputController->update();

		this->buttons.at(this->lastButton)->setSelected(false);
		this->buttons.at(this->actualButton)->setSelected(true);

		view->render();

	}
}

