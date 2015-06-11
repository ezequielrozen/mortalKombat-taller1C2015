#include "CharacterSelection.h"

CharacterSelection::CharacterSelection(SDL_Renderer* renderer, InputController* inputController) {
	
	this->inputController = inputController;

	this->buttons1 = new Button*[12];
	this->buttons2 = new Button*[12];

	this->buttons1[0] = new Button("character", true);
	for (int i = 1; i < 12; i++) {
		this->buttons1[i] = new Button("character", false);
	}

	this->buttons2[0] = new Button("character2", true);
	for (int i = 1; i < 12; i++) {
		this->buttons2[i] = new Button("character2", false);
	}

	this->view = new CharacterSelectionView(renderer, this->buttons1, this->buttons2);

	this->buttonInfo[0] = {0,1,false};
	this->buttonInfo[1] = {0,1,false};

}

CharacterSelection::~CharacterSelection() {
	delete view;
	for(int i = 0; i < 12; i++) {
        delete buttons1[i];
        delete buttons2[i];
    }

    delete [] buttons1;
    delete [] buttons2;

}

void CharacterSelection::linkInputController() {
	this->inputController->setCharacterSelection(this);
}

void CharacterSelection::moveUp(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;

		if (this->buttonInfo[n].actualButton > 3) {
			this->buttonInfo[n].actualButton = this->buttonInfo[n].actualButton - 4;
		}
		else {
			this->buttonInfo[n].actualButton = this->buttonInfo[n].actualButton + 8;
		}
	}
}

void CharacterSelection::moveDown(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;
	
		if (this->buttonInfo[n].actualButton < 8) {
			this->buttonInfo[n].actualButton = buttonInfo[n].actualButton + 4;
		}
		else {
			this->buttonInfo[n].actualButton = buttonInfo[n].actualButton - 8;
		}
	}
}

void CharacterSelection::moveRight(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;

		if (this->buttonInfo[n].actualButton < 11) {
			this->buttonInfo[n].actualButton++;
		}
		else {
			this->buttonInfo[n].actualButton = 0;
		}
	}
}

void CharacterSelection::moveLeft(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;

		if (this->buttonInfo[n].actualButton > 0) {
			this->buttonInfo[n].actualButton--;
		}
		else {
			this->buttonInfo[n].actualButton = 11;
		}
	}
}

void CharacterSelection::select(int n) {
	if (!(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].buttonPressed = true;
	}
}

void CharacterSelection::switchSelected() {
	this->buttons1[this->buttonInfo[0].lastButton]->setSelected(false);
	this->buttons1[this->buttonInfo[0].actualButton]->setSelected(true);
	this->buttons2[this->buttonInfo[1].lastButton]->setSelected(false);
	this->buttons2[this->buttonInfo[1].actualButton]->setSelected(true);
}

void CharacterSelection::randomSelection() {
	if (this->inputController->isAIEnabled() && (rand() % 10) == 0 && !this->buttonInfo[1].buttonPressed) {
		this->buttonInfo[1].lastButton = this->buttonInfo[1].actualButton;

		if (this->buttonInfo[1].actualButton < 11) {
			this->buttonInfo[1].actualButton++;
		}
		else {
			this->buttonInfo[1].actualButton = 0;
		}

		if ((rand() % 10) == 0) {
			this->buttonInfo[1].buttonPressed = true;
		}
	}
}

void CharacterSelection::reset() {

	this->buttonInfo[0].lastButton = this->buttonInfo[0].actualButton;
	this->buttonInfo[0].actualButton = 0;
	this->buttonInfo[0].buttonPressed = false;
	this->buttonInfo[1].lastButton = this->buttonInfo[1].actualButton;
	this->buttonInfo[1].actualButton = 0;
	this->buttonInfo[1].buttonPressed = false;	

	this->switchSelected();

}

void CharacterSelection::loop() {
	
	while ( inputController->getEvent()->type != SDL_QUIT && !(this->buttonInfo[0].buttonPressed && this->buttonInfo[1].buttonPressed)) {
		inputController->checkEvent();
		inputController->update();

		this->randomSelection();

		this->switchSelected();

		view->render();

	}
	this->reset();
}

