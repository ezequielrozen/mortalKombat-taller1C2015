#include "StageManager.h"
#include "../controller/ModeSelectionController.h"
#include "../controller/CharacterSelectionController.h"

StageManager::StageManager(char* filePath) {

	this->gameLoader = new GameLoader();
	this->gameLoader->loadJSON(filePath);

	this->window = NULL;
    this->window = SDL_CreateWindow("Mortal Kombat", 0, 0, Util::getInstance()->getWindowWidth(), Util::getInstance()->getWindowHeight(), SDL_WINDOW_SHOWN);
    if (this->window == NULL) {

        std::cout << "Window couldn't be created" << std::endl;
    }
	this->stageController = NULL;
	this->inputController = new InputController(this->stageController);
//	this->setStageController(new ModeSelectionController()); // Acá deberíamos pasarle al ModeSelectionController el ModeSelection (modelo) para que lo actualice

    this->renderer = NULL;
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_TARGETTEXTURE);
	this->modeSelection = new ModeSelection(this->renderer, this->inputController);
    this->characterSelection = new CharacterSelection(this->renderer, this->inputController);

	this->game = new Game(this->gameLoader, this->renderer, this->inputController);

}

StageManager::~StageManager() {
	delete this->game;
	delete this->characterSelection;
	delete this->modeSelection;
	delete this->gameLoader;

	SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

	delete this->stageController;
	delete this->inputController;

}

bool StageManager::mainLoop() {
	bool restart = false;
	while(inputController->getEvent()->type != SDL_QUIT && !restart) {
		
		this->setStageController(new ModeSelectionController());
		this->modeSelection->linkInputController();
		GameModes mode = this->modeSelection->loop();
		
		if (mode == OneVsAI) {
			this->inputController->enableAI();
			ComboButtonsView::getInstance()->deactivate();
		} else if (mode == Practice) {
			this->inputController->enablePracticeAI();
			this->game->enablePracticeMode();
			ComboButtonsView::getInstance()->activate();
		} else {
			this->inputController->disableAI();
			ComboButtonsView::getInstance()->deactivate();
		}
		
		setStageController(new CharacterSelectionController());
		this->characterSelection->linkInputController();
		this->characterSelection->loop();
		
		setStageController(new EventController(this->gameLoader->getCombo1(), this->gameLoader->getCombo2(), this->gameLoader->getFatality()));
		this->game->setCharacterNames(this->characterSelection->getNameOne(), this->characterSelection->getNameTwo());
		this->characterSelection->restartNames();
		restart = this->game->GameLoop(mode);
		
	}

	return restart;
}

void StageManager::setStageController(MKStageController* stageController) {
	if (this->stageController != NULL) {
		delete this->stageController;
	}
	this->stageController = stageController;
	this->inputController->setStageController(this->stageController);
}