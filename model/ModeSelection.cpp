#include "ModeSelection.h"
#include "../view/SoundManager.h"

ModeSelection::ModeSelection(SDL_Renderer* renderer, InputController* inputController) {
	
	this->inputController = inputController; // ESTO DEBERÍA VOLAR, EL CONTROLLER CONOCE Y ACTUALICA EL MODELO, PERO EL MODELO NO (Creo)
	//this->inputController = new InputController(new EventController());
	
	int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();
	
	this->buttons = new Button*[3];

	this->buttons[0] = new Button("1v1", true, 0.343*scWidth, 0.29*scHeight, 0.314*scWidth, 0.16*scHeight);
	this->buttons[1] = new Button("1vPC", false, 0.343*scWidth, 0.51*scHeight, 0.314*scWidth, 0.16*scHeight);
	this->buttons[2] = new Button("practice", false, 0.343*scWidth, 0.73*scHeight, 0.314*scWidth, 0.16*scHeight);
	this->view = new ModeSelectionView(renderer, this->buttons);
	this->index = 0;
	this->selectionMade = false;
	this->mouseOnButton = false;
	this->splashScreen = true;
}

ModeSelection::~ModeSelection() {

    for (int i = 0; i < 3; i++) {
    	delete this->buttons[i];
    }
    delete [] buttons;

	delete view;
}

GameModes ModeSelection::loop() {

	view->setSplashScreen(true);
	this->splashScreen = true;
	while ( inputController->getEvent()->type != SDL_QUIT) {
		inputController->checkEvent();
		inputController->update();
		view->render();

		if (selectionMade) {
			selectionMade = false;
			if (buttons[index]->getName() == "1v1") {
				return OneVsTwo;
			}
			if (buttons[index]->getName() == "1vPC") {
				return OneVsAI;
			}
			if (buttons[index]->getName() == "practice") {
				return Practice;
			}
		}

	}


}

void ModeSelection::linkInputController() {
	this->inputController->setModeSelection(this);
}

void ModeSelection::moveUp() {
	if (this->splashScreen) {
		this->splashScreen = false;
		this->view->setSplashScreen(false);
	}
	else {
		if(this->index > 0) {
			this->index--;
			this->buttons[index+1]->setSelected(false);
			this->buttons[index]->setSelected(true);
			this->mouseOnButton = false;
			SoundManager::getInstance()->playSound("select");
		}
	}
}

void ModeSelection::moveDown() {
	if (this->splashScreen) {
		this->splashScreen = false;
		this->view->setSplashScreen(false);
	}
	else {
		if(this->index < 2) {
			index++;
			this->buttons[index-1]->setSelected(false);
			this->buttons[index]->setSelected(true);
			this->mouseOnButton = false;
			SoundManager::getInstance()->playSound("select");
		}
	}
}

void ModeSelection::select() {
	if (this->splashScreen) {
		this->splashScreen = false;
		this->view->setSplashScreen(false);
	}
	else {
		this->selectionMade = true;
		SoundManager::getInstance()->playSound("confirmselection");
	}
}

void ModeSelection::updateMousePosition(unsigned short x, unsigned short y) {
	if (!this->splashScreen) {
		bool mouseOnButtonAux = false;

		for (int i = 0; i < 3; i++) {
			if (buttons[i]->checkBoundaries(x, y)) {
				if (!buttons[i]->isSelected()) {
					SoundManager::getInstance()->playSound("select");
				}
				this->buttons[index]->setSelected(false);
				index = i;
				this->buttons[i]->setSelected(true);
				mouseOnButtonAux = true;
			}
		}

		this->mouseOnButton = mouseOnButtonAux;
	}
}

void ModeSelection::mouseSelect() {
	if (this->splashScreen) {
		this->splashScreen = false;
		this->view->setSplashScreen(false);
	}
	else {
		if (this->mouseOnButton) {
			this->selectionMade = true;
			SoundManager::getInstance()->playSound("confirmselection");
		}
	}
}

void ModeSelection::skipSplashScreen() {
	this->splashScreen = false;
	this->view->setSplashScreen(false);
}