#include "ModeSelection.h"

ModeSelection::ModeSelection(SDL_Renderer* renderer, InputController* inputController) {
	this->view = new ModeSelectionView(renderer);
	this->inputController = inputController; // ESTO DEBERÍA VOLAR, EL CONTROLLER CONOCE Y ACTUALICA EL MODELO, PERO EL MODELO NO (Creo)
	//this->inputController = new InputController(new EventController());
}

ModeSelection::~ModeSelection() {
	delete view;
}

void ModeSelection::loop() {

	while (!(inputController->getEvent()->type == SDL_KEYDOWN && inputController->getEvent()->key.keysym.sym == SDLK_m) && inputController->getEvent()->type != SDL_QUIT) {
		inputController->checkEvent();
		inputController->update();
		view->render();
	}

}