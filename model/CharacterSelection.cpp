#include "CharacterSelection.h"

CharacterSelection::CharacterSelection(SDL_Renderer* renderer, InputController* inputController) {
	this->view = new CharacterSelectionView(renderer);
	this->inputController = inputController;

}

CharacterSelection::~CharacterSelection() {
	delete view;
}

void CharacterSelection::linkInputController() {
	this->inputController->setCharacterSelection(this);
}

void CharacterSelection::moveUp() {
	cout << "UP" << endl;
}

void CharacterSelection::moveDown() {
	cout << "DOWN" << endl;
}

void CharacterSelection::moveRight() {
	cout << "RIGHT" << endl;
}

void CharacterSelection::moveLeft() {
	cout << "LEFT" << endl;
}

void CharacterSelection::loop() {
	
	while ( inputController->getEvent()->type != SDL_QUIT && (!(inputController->getEvent()->type == SDL_KEYDOWN && inputController->getEvent()->key.keysym.sym == SDLK_m))) {
		inputController->checkEvent();
		inputController->update();
		view->render();

	}
}
