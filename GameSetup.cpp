#include <iostream>
#include "GameSetup.h"

GameSetup::GameSetup(bool* quit, int ScreenWidth, int ScreenHeight) {

	window = NULL;
	window = SDL_CreateWindow("Mortal Kombat", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) {

		std::cout << "Window couldn't be created" << std::endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

	mainEvent = new SDL_Event();


}

GameSetup::~GameSetup() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* GameSetup::getRenderer() {
	return renderer;
}

SDL_Event* GameSetup::getMainEvent() {
	return mainEvent;
}

void GameSetup::Begin() {

	SDL_PollEvent(this->getMainEvent());
	SDL_RenderClear(this->getRenderer());
}

void GameSetup::End() {

	SDL_RenderPresent(this->getRenderer());
}
