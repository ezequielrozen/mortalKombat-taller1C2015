#include "Game.h"

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
    this->scorpion = new MKCharacter(INITIAL_POSITION_X, INITIAL_POSITION_Y, this->gameLoader->getCharacterWith(),
                                     this->gameLoader->getCharacterHeight(), this->gameLoader->getZ_index());
    this->gameView = new GameView(ScreenWidth, ScreenHeight, scorpion, stage, oponentSide);
    this->gameController = new GameController();
    this->cameraController = new CameraController();
}

Game::~Game()
{
    delete scorpion;
    delete gameView;
    delete gameController;
    delete cameraController;
}

void Game::GameLoop() {
    while (gameController->getEvent()->type != SDL_QUIT && gameController->getEvent()->key.keysym.sym != SDLK_r) {
        gameController->checkEvent();
        gameView->startRender();
        gameView->Render();
        gameController->update(scorpion);
        cameraController->update(scorpion, stage->getLayers());
        gameView->endRender();
        SDL_Delay(15);
    }
}
