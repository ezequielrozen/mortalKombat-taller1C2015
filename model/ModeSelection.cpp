#include "ModeSelection.h"

ModeSelection::ModeSelection(SDL_Renderer* renderer) {
	this->view = new ModeSelectionView(renderer);
	this->inputController = new InputController();
}

ModeSelection::~ModeSelection() {
	delete view;
}

void ModeSelection::loop() {

	while (!(inputController->getEvent()->type == SDL_KEYDOWN && inputController->getEvent()->key.keysym.sym == SDLK_m) && inputController->getEvent()->type != SDL_QUIT) {
		inputController->checkEvent();
		view->render();
	}

}