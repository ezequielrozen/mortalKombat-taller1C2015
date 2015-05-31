#include "ModeSelection.h"

ModeSelection::ModeSelection(SDL_Renderer* renderer, InputController* inputController) {
	
	this->inputController = inputController; // ESTO DEBERÍA VOLAR, EL CONTROLLER CONOCE Y ACTUALICA EL MODELO, PERO EL MODELO NO (Creo)
	//this->inputController = new InputController(new EventController());
	
	this->buttons.push_back(new Button("1v1",true));
	this->buttons.push_back(new Button("1vPC",false));
	this->buttons.push_back(new Button("practice",false));

	this->view = new ModeSelectionView(renderer, this->buttons);

}

ModeSelection::~ModeSelection() {
	for(int i = 0; i < 3; i++) {
        delete buttons.at(i);
    }

	delete view;
}

GameModes ModeSelection::loop() {

	while ( inputController->getEvent()->type != SDL_QUIT) {
		inputController->checkEvent();
		inputController->update();
		view->render();
		//	Esto es temporal hasta que tengamos hecha la pantalla de seleccion de juego.
		if (peviousKey == SDLK_a && inputController->getEvent()->key.keysym.sym == SDLK_a) {
			return OneVsAI;
		} else if (peviousKey == SDLK_s && inputController->getEvent()->key.keysym.sym == SDLK_s) {
			return OneVsTwo;
		} else if (peviousKey == SDLK_d && inputController->getEvent()->key.keysym.sym == SDLK_d) {
			return Practice;
		} else {
			peviousKey = inputController->getEvent()->key.keysym.sym;
		}
	}

}