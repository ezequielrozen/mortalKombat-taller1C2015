#include "Game.h"
#include "../controller/JoystickController.h"
#include "character/Dizzy.h"
#include "character/Victory.h"

Game::Game(GameLoader* aGameLoader, char* filePath) {
    this->gameLoader = aGameLoader;
    this->initGame(filePath);
}

void Game::initGame(char* filePath) {
    this->gameLoader->loadJSON(filePath);
    this->ScreenWidth = Util::getInstance()->getWindowWidth();
    this->ScreenHeight = Util::getInstance()->getWindowHeight();
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

    this->gameView = new GameView(ScreenWidth, ScreenHeight, scorpion, raiden, stage, oponentSide, this->gameLoader->getPainter());
//    this->gameController = new GameController();
//    GameController::setVibrating(false);
    this->inputController = new InputController();
    InputController::setVibrating(false);
    this->cameraController = new CameraController();
    this->collider = new Collider();
}

Game::~Game() {
    delete gameLoader;
    delete gameView;
//    delete gameController;
    delete inputController;
    delete cameraController;
    delete collider;
}

//bool Game::GameLoop() {
//
//    bool cameraMoved;
//
//    while (gameController->getEvent()->type != SDL_QUIT) {
//        gameController->checkEvent();
//        gameView->startRender();
//        gameView->Render();
//        if ( scorpion->isAlive() && raiden->isAlive() )
//            gameController->update(scorpion, raiden);
//        else // fin de juego. loguearlo (1 sola vez)
//            gameController->victory(scorpion, raiden);
//        cameraMoved = cameraController->update(scorpion, raiden, stage->getLayers());
//        collider->update(scorpion, raiden, cameraMoved);
//        gameView->endRender();
//        SDL_Delay(15);
//
//        if (peviousKey == SDLK_r && gameController->getEvent()->key.keysym.sym == SDLK_e) {
//            return true;
//        }
//        else {
//        	peviousKey = gameController->getEvent()->key.keysym.sym;
//        }
//
//    }
//    return false;
//}


bool Game::GameLoop() {

    bool cameraMoved;

    while (inputController->getEvent()->type != SDL_QUIT) {
    	inputController->checkEvent();
        gameView->startRender();
        gameView->Render();
        inputController->update(scorpion, raiden);
        updateGameState();
        cameraMoved = cameraController->update(scorpion, raiden, stage->getLayers());
        collider->update(scorpion, raiden, cameraMoved);

        gameView->endRender();
        SDL_Delay(GAMEDELAY);

        if (peviousKey == SDLK_r && inputController->getEvent()->key.keysym.sym == SDLK_e) {
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
        scorpion->setState(new Dizzy());
        scorpion->setPosY(this->stage->getFloor());
        raiden->setState(new Victory());
        raiden->setPosY(this->stage->getFloor());

    } else if (!raiden->isAlive()) {
        raiden->setState(new Dizzy());
        raiden->setPosY(this->stage->getFloor());
        scorpion->setState(new Victory());
        scorpion->setPosY(this->stage->getFloor());
    }
}