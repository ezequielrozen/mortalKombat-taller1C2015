#include "ModeSelection.h"

ModeSelection::ModeSelection(SDL_Renderer* renderer, InputController* inputController) {
	
	this->inputController = inputController; // ESTO DEBERÍA VOLAR, EL CONTROLLER CONOCE Y ACTUALICA EL MODELO, PERO EL MODELO NO (Creo)
	//this->inputController = new InputController(new EventController());
	
	this->buttons.push_back(new Button("1v1",true));
	this->buttons.push_back(new Button("1vPC",false));
	this->buttons.push_back(new Button("practice",false));
	this->view = new ModeSelectionView(renderer, this->buttons);
	this->index = 0;
	this->selectionMade = false;
	this->inputController->setModeSelection(this);
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

		if (selectionMade) {
			if (buttons.at(index)->getName() == "1v1")
				return OneVsTwo;
			if (buttons.at(index)->getName() == "1vPC")
				return OneVsAI;
			if (buttons.at(index)->getName() == "practice")
				return Practice;
		}
		//	Esto es temporal hasta que tengamos hecha la pantalla de seleccion de juego.
		/*if (peviousKey == SDLK_a && inputController->getEvent()->key.keysym.sym == SDLK_a) {
			return OneVsAI;
		} else if (peviousKey == SDLK_s && inputController->getEvent()->key.keysym.sym == SDLK_s) {
			return OneVsTwo;
		} else if (peviousKey == SDLK_d && inputController->getEvent()->key.keysym.sym == SDLK_d) {
			return Practice;
		} else {
			peviousKey = inputController->getEvent()->key.keysym.sym;
		}*/

	}

}

void ModeSelection::moveUp() {
	cout << "Move Down" << endl;

	if(this->index > 0) {
		this->index--;
		this->buttons.at(index+1)->setSelected(false);
		this->buttons.at(index)->setSelected(true);
	}
}

void ModeSelection::moveDown() {
	if(this->index < 2) {
		index++;
		this->buttons.at(index-1)->setSelected(false);
		this->buttons.at(index)->setSelected(true);
	}
}

void ModeSelection::select() {
	this->selectionMade = true;
}
