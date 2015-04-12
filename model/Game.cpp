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
    this->scorpion = new MKCharacter(0.5*(Util::getInstance()->getLogicalWindowWidth()-this->gameLoader->getCharacterWidth()), this->stage->getFloor(), this->gameLoader->getCharacterWidth(),
                                     this->gameLoader->getCharacterHeight(), this->gameLoader->getZ_index(),
                                     Util::getInstance()->getWalk(), Util::getInstance()->getStance(),
                                     Util::getInstance()->getJump(), Util::getInstance()->getSideJump());
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

bool Game::GameLoop() {

    while (gameController->getEvent()->type != SDL_QUIT) {
        gameController->checkEvent();
        gameView->startRender();
        gameView->Render();
        gameController->update(scorpion);
        cameraController->update(scorpion, stage->getLayers());
        gameView->endRender();
        SDL_Delay(15);

        if (gameController->getEvent()->key.keysym.sym == SDLK_r) {
            return true;
        }
    }
    return false;
}
