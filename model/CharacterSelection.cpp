#include "CharacterSelection.h"
#include "../view/SoundManager.h"

CharacterSelection::CharacterSelection(SDL_Renderer* renderer, InputController* inputController) {
	
	this->inputController = inputController;

	int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();

	this->buttons1 = new Button*[12];
	this->buttons2 = new Button*[12];
	//this->nameButtons = new Button*[2];

	float displaceX = 0.1588;
	float displaceY = 0.212;
	int i = 0;
	int j = 0;
    
	while (i < 3) {
		while (j < 4) {
			buttons1[(4*i)+j] = new Button("character", false, (0.189+(displaceX*j))*scWidth, (0.148+(displaceY*i))*scHeight, 0.1488*scWidth, 0.202*scHeight);
			buttons2[(4*i)+j] = new Button("character2", false, (0.189+(displaceX*j))*scWidth, (0.148+(displaceY*i))*scHeight, 0.1488*scWidth, 0.202*scHeight);
			j++;
		}
		i++;
		j = 0;
	}

	this->buttons1[0]->setSelected(true);
	this->buttons2[0]->setSelected(true);

	//this->nameButtons[0] = new Button("name", false, 0,0,0,0);
	//this->nameButtons[0] = new Button("name", false, 0,0,0,0);

	this->view = new CharacterSelectionView(renderer, this->buttons1, this->buttons2);

	this->buttonInfo[0] = {0,1,false};
	this->buttonInfo[1] = {0,1,false};

	this->names[0] = "SCORPION";
	this->names[1] = "RAIDEN";

	this->mouseOnButton = false;
	this->nameButtonIndex = 0;

	this->characterSelectionFinished = false;

}

CharacterSelection::~CharacterSelection() {
	delete view;
	for(int i = 0; i < 12; i++) {
        delete buttons1[i];
        delete buttons2[i];
    }

   	//delete nameButtons[0];
   	//delete nameButtons[1];

   	//delete [] nameButtons;
    delete [] buttons1;
    delete [] buttons2;

}

void CharacterSelection::linkInputController() {
	this->inputController->setCharacterSelection(this);
}

void CharacterSelection::moveUp(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;
		SoundManager::getInstance()->playSound("select2");

		if (this->buttonInfo[n].actualButton > 3) {
			this->buttonInfo[n].actualButton = this->buttonInfo[n].actualButton - 4;
		}
		else {
			this->buttonInfo[n].actualButton = this->buttonInfo[n].actualButton + 8;
		}
		if (n == 0) {
			this->mouseOnButton = false;
		}
	}
}

void CharacterSelection::moveDown(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;
		SoundManager::getInstance()->playSound("select2");

		if (this->buttonInfo[n].actualButton < 8) {
			this->buttonInfo[n].actualButton = buttonInfo[n].actualButton + 4;
		}
		else {
			this->buttonInfo[n].actualButton = buttonInfo[n].actualButton - 8;
		}
		if (n == 0) {
			this->mouseOnButton = false;
		}
	}
}

void CharacterSelection::moveRight(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;
		SoundManager::getInstance()->playSound("select2");

		if (this->buttonInfo[n].actualButton < 11) {
			this->buttonInfo[n].actualButton++;
		}
		else {
			this->buttonInfo[n].actualButton = 0;
		}
		if (n == 0) {
			this->mouseOnButton = false;
		}
	}

	if (this->buttonInfo[0].buttonPressed && this->buttonInfo[1].buttonPressed && n == 0) {
		this->nameButtonIndex = 1;
	}
}

void CharacterSelection::moveLeft(int n) {
	if (!this->buttonInfo[n].buttonPressed && !(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].lastButton = this->buttonInfo[n].actualButton;
		SoundManager::getInstance()->playSound("select2");

		if (this->buttonInfo[n].actualButton > 0) {
			this->buttonInfo[n].actualButton--;
		}
		else {
			this->buttonInfo[n].actualButton = 11;
		}
		if (n == 0) {
			this->mouseOnButton = false;
		}
	}

	if (this->buttonInfo[0].buttonPressed && this->buttonInfo[1].buttonPressed && n == 0) {
		this->nameButtonIndex = 0;
	}
}

void CharacterSelection::select(int n) {
	if (n == 0 && this->buttonInfo[0].buttonPressed && this->buttonInfo[1].buttonPressed) {
		this->updateName("L");
	}
	else if (n == 1 && this->buttonInfo[0].buttonPressed && this->buttonInfo[1].buttonPressed) {
		this->updateName("G");
	}

	if (!(n == 1 && this->inputController->isAIEnabled())) {
		this->buttonInfo[n].buttonPressed = true;
		SoundManager::getInstance()->playSound("confirmselection");
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

	this->mouseOnButton = false;
	this->characterSelectionFinished = false;

}


void CharacterSelection::mouseSelect() {
	if (this->mouseOnButton) {
		this->buttonInfo[0].buttonPressed = true;
	}
}

void CharacterSelection::updateMousePosition(unsigned short x, unsigned short y) {
	bool mouseOnButtonAux = false;

	for (int i = 0; i < 12; i++) {
		if (buttons1[i]->checkBoundaries(x, y) && !this->buttonInfo[0].buttonPressed) {
			this->buttonInfo[0].lastButton = this->buttonInfo[0].actualButton;
			this->buttonInfo[0].actualButton = i;
			mouseOnButtonAux = true;
		}
	}

	this->mouseOnButton = mouseOnButtonAux;
}

void CharacterSelection::updateName(string letter) {
	if (this->buttonInfo[0].buttonPressed && this->buttonInfo[1].buttonPressed) {
		if (letter == "DEL" ) {
			if (!this->names[0].empty() || this->names[1].empty()) {
				this->names[nameButtonIndex].pop_back();
			}
		} else if (letter == "ENTER") {
			this->characterSelectionFinished = true;
		}
		else {
			this->names[nameButtonIndex] = this->names[nameButtonIndex] + letter;
		}
		if (!(this->names[0].empty() || this->names[1].empty())) {
			this->view->updateCharacterNames(this->names[0], this->names[1]);
		}
	}
	
}

void CharacterSelection::loop() {
	
	while ( inputController->getEvent()->type != SDL_QUIT && !this->characterSelectionFinished) {
		inputController->checkEvent();
		inputController->update();

		this->randomSelection();

		this->switchSelected();

		this->view->render();

	}
	this->reset();
}

