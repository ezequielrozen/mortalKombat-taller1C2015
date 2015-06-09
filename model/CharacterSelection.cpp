#include "CharacterSelection.h"

CharacterSelection::CharacterSelection(SDL_Renderer* renderer, InputController* inputController) {
	
	this->inputController = inputController;

	this->buttons1.push_back(new Button("character", true));
	for (int i = 1; i < 12; i++) {
		this->buttons1.push_back(new Button("character", false));
	}

	this->buttons2.push_back(new Button("character2", true));
	for (int i = 1; i < 12; i++) {
		this->buttons2.push_back(new Button("character2", false));
	}

	this->view = new CharacterSelectionView(renderer, this->buttons1, this->buttons2);

	this->buttonInfo.push_back({0,1,false});
	this->buttonInfo.push_back({0,1,false});

}

CharacterSelection::~CharacterSelection() {
	delete view;
	for(int i = 0; i < 12; i++) {
        delete buttons1.at(i);
        delete buttons2.at(i);
    }
}

void CharacterSelection::linkInputController() {
	this->inputController->setCharacterSelection(this);
}

void CharacterSelection::moveUp(int n) {
	if (!this->buttonInfo.at(n).buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo.at(n).lastButton = this->buttonInfo.at(n).actualButton;

		if (this->buttonInfo.at(n).actualButton > 3) {
			this->buttonInfo.at(n).actualButton = this->buttonInfo.at(n).actualButton - 4;
		}
		else {
			this->buttonInfo.at(n).actualButton = this->buttonInfo.at(n).actualButton + 8;
		}
	}
}

void CharacterSelection::moveDown(int n) {
	if (!this->buttonInfo.at(n).buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo.at(n).lastButton = this->buttonInfo.at(n).actualButton;
	
		if (this->buttonInfo.at(n).actualButton < 8) {
			this->buttonInfo.at(n).actualButton = buttonInfo.at(n).actualButton + 4;
		}
		else {
			this->buttonInfo.at(n).actualButton = buttonInfo.at(n).actualButton - 8;
		}
	}
}

void CharacterSelection::moveRight(int n) {
	if (!this->buttonInfo.at(n).buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo.at(n).lastButton = this->buttonInfo.at(n).actualButton;

		if (this->buttonInfo.at(n).actualButton < 11) {
			this->buttonInfo.at(n).actualButton++;
		}
		else {
			this->buttonInfo.at(n).actualButton = 0;
		}
	}
}

void CharacterSelection::moveLeft(int n) {
	if (!this->buttonInfo.at(n).buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo.at(n).lastButton = this->buttonInfo.at(n).actualButton;

		if (this->buttonInfo.at(n).actualButton > 0) {
			this->buttonInfo.at(n).actualButton--;
		}
		else {
			this->buttonInfo.at(n).actualButton = 11;
		}
	}
}

void CharacterSelection::select(int n) {
	if (!(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo.at(n).buttonPressed = true;
	}
}

void CharacterSelection::switchSelected() {
	this->buttons1.at(this->buttonInfo.at(0).lastButton)->setSelected(false);
	this->buttons1.at(this->buttonInfo.at(0).actualButton)->setSelected(true);
	this->buttons2.at(this->buttonInfo.at(1).lastButton)->setSelected(false);
	this->buttons2.at(this->buttonInfo.at(1).actualButton)->setSelected(true);
}

void CharacterSelection::randomSelection() {
	if (this->inputController->isAIEnabled() && (rand() % 10) == 0) {
		this->buttonInfo.at(1).lastButton = this->buttonInfo.at(1).actualButton;

		if (this->buttonInfo.at(1).actualButton < 11) {
			this->buttonInfo.at(1).actualButton++;
		}
		else {
			this->buttonInfo.at(1).actualButton = 0;
		}

		if ((rand() % 10) == 0) {
			this->buttonInfo.at(1).buttonPressed = true;
		}
	}
}

void CharacterSelection::reset() {

	this->buttonInfo.at(0).lastButton = this->buttonInfo.at(0).actualButton;
	this->buttonInfo.at(0).actualButton = 0;
	this->buttonInfo.at(0).buttonPressed = false;
	this->buttonInfo.at(1).lastButton = this->buttonInfo.at(1).actualButton;
	this->buttonInfo.at(1).actualButton = 0;
	this->buttonInfo.at(1).buttonPressed = false;	

	this->switchSelected();

}

void CharacterSelection::loop() {
	
	while ( inputController->getEvent()->type != SDL_QUIT && !(this->buttonInfo.at(0).buttonPressed && this->buttonInfo.at(1).buttonPressed)) {
		inputController->checkEvent();
		inputController->update();

		this->randomSelection();

		this->switchSelected();

		view->render();

	}
	this->reset();
}

