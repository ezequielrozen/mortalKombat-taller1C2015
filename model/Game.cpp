#include "Game.h"
#include "../controller/JoystickController.h"
#include "character/Dizzy.h"
#include "character/Victory.h"
#include <SDL2/SDL_mixer.h>

Game::Game(GameLoader* aGameLoader, SDL_Renderer* renderer, InputController* inputController) {
    this->gameLoader = aGameLoader;
    this->initGame(renderer, inputController);
    diedTimeElapsed = 0;
}

void Game::initGame(SDL_Renderer* renderer, InputController* inputController) {
    //this->gameLoader->loadJSON(filePath);
    //this->ScreenWidth = Util::getInstance()->getWindowWidth();
    //this->ScreenHeight = Util::getInstance()->getWindowHeight();
    this->stage = this->gameLoader->getStage();
    this->oponentSide = this->gameLoader->getOponentSide();

    this->scorpion = this->gameLoader->getCharacters()->front();
    this->raiden = this->gameLoader->getCharacters()->back();
    if (this->scorpion->getX() == this->raiden->getX()) {
        this->scorpion->setInitialPosition(0.2*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
        this->raiden->setInitialPosition(0.8*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
    };
    //This is very important!
    this->scorpion->setPosY(this->stage->getFloor());
    this->scorpion->setStageFloor(this->stage->getFloor());
    this->raiden->setPosY(this->stage->getFloor());
    this->raiden->setStageFloor(this->stage->getFloor());

    this->gameView = new GameView(renderer, scorpion, raiden, stage, oponentSide, this->gameLoader->getPainter());
    this->inputController = inputController;
    this->inputController->setCharacters(scorpion, raiden);
    InputController::setVibrating(false);
    this->cameraController = new CameraController();
    this->collider = new Collider();

    //this->comboManager = new ComboManager();
}

Game::~Game() {
    delete gameView;
    delete cameraController;
    delete collider;
}

bool Game::GameLoop() {

    bool cameraMoved;

    while (inputController->getEvent()->type != SDL_QUIT) {
    	inputController->checkEvent();
        gameView->startRender();
        gameView->Render();
        inputController->update();
        updateGameState();
        cameraMoved = cameraController->update(scorpion, raiden, stage->getLayers());
        collider->update(scorpion, raiden, cameraMoved);

        gameView->endRender();
        SDL_Delay(GAMEDELAY);

        if (peviousKey == SDLK_r && inputController->getEvent()->key.keysym.sym == SDLK_r) {
            return true;
        }
        else {
        	peviousKey = inputController->getEvent()->key.keysym.sym;
        }

    }
    return false;
}

void Game::updateGameState() {
    if (!scorpion->isAlive()) {
    	if (scorpion->getState() != "ReceivingFire"){
			scorpion->setState(new Dizzy());
			scorpion->setPosY(this->stage->getFloor());
	//        raiden->setState(new Victory());
			raiden->setPosY(this->stage->getFloor());
    	}

    } else if (!raiden->isAlive()) {
    	if (raiden->getState() != "ReceivingFire"){
			raiden->setState(new Dizzy());
			raiden->setPosY(this->stage->getFloor());
			if (diedTimeElapsed == 0) diedTimeElapsed = SDL_GetTicks();
			if ((SDL_GetTicks() - diedTimeElapsed>=  TIME_FOR_DOING_FATALITY) && scorpion->getState() == "Stance")
				scorpion->setState(new Victory());
			scorpion->setPosY(this->stage->getFloor());
    	}
    }
}
