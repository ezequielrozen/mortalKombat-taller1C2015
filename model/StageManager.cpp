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
	this->setStageController(new ModeSelectionController()); // Acá deberíamos pasarle al ModeSelectionController el ModeSelection (modelo) para que lo actualice

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

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);

	delete this->stageController;
	delete this->inputController;
}

bool StageManager::mainLoop() {

	GameModes mode = this->modeSelection->loop();
	if (mode == OneVsAI) {
		this->inputController->enableAI();
	}

	setStageController(new CharacterSelectionController());
	this->characterSelection->linkInputController();
	this->characterSelection->loop();

	setStageController(new EventController());
	bool restart = this->game->GameLoop();

	return restart;
}

void StageManager::setStageController(MKStageController* stageController) {
	if (this->stageController != NULL) {
		delete this->stageController;
	}
	else {
		this->inputController = new InputController(stageController);
	}
	this->stageController = stageController;
	this->inputController->setStageController(this->stageController);
}