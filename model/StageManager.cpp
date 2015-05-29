#include "StageManager.h"

StageManager::StageManager(char* filePath) {

	this->gameLoader = new GameLoader();
	this->gameLoader->loadJSON(filePath);

	this->window = NULL;
    this->window = SDL_CreateWindow("Mortal Kombat", 0, 0, Util::getInstance()->getWindowWidth(), Util::getInstance()->getWindowHeight(), SDL_WINDOW_SHOWN);
    if (this->window == NULL) {

        std::cout << "Window couldn't be created" << std::endl;
    }

    this->renderer = NULL;
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_TARGETTEXTURE);

	this->modeSelection = new ModeSelection(this->renderer);
    this->characterSelection = new CharacterSelection(this->renderer);
    this->game = new Game(this->gameLoader, this->renderer);

}

StageManager::~StageManager() {
	delete this->game;
	delete this->characterSelection;
	delete this->modeSelection;
	delete this->gameLoader;

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}

bool StageManager::mainLoop() {
	
	this->modeSelection->loop();

	this->characterSelection->loop();

	bool restart = this->game->GameLoop();

	return restart;
}