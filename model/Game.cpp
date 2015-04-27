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
    this->scorpion = new MKCharacter(0.2*(Util::getInstance()->getLogicalWindowWidth()-this->gameLoader->getCharacterWidth()), this->stage->getFloor(), this->gameLoader->getCharacterWidth(),
                                     this->gameLoader->getCharacterHeight(), this->gameLoader->getZ_index(),
                                     Util::getInstance()->getWalk(0), Util::getInstance()->getStance(0),
                                     Util::getInstance()->getJump(0), Util::getInstance()->getSideJump(0));
    this->raiden = new MKCharacter(0.8*(Util::getInstance()->getLogicalWindowWidth()-this->gameLoader->getCharacterWidth()), this->stage->getFloor(), this->gameLoader->getCharacterWidth(),
                                     this->gameLoader->getCharacterHeight(), this->gameLoader->getZ_index(),
                                     Util::getInstance()->getWalk(1), Util::getInstance()->getStance(1),
                                     Util::getInstance()->getJump(1), Util::getInstance()->getSideJump(1));
    this->gameView = new GameView(ScreenWidth, ScreenHeight, scorpion, raiden, stage, oponentSide);
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

//        if (gameController->getEvent()->key.keysym.sym != 0)
//        	cout << gameController->getEvent()->key.keysym.sym << endl;

        if (peviousKey == SDLK_r && gameController->getEvent()->key.keysym.sym == SDLK_e) {
            return true;
        }
        else
        {
        	peviousKey = gameController->getEvent()->key.keysym.sym;
        }

    }
    return false;
}
