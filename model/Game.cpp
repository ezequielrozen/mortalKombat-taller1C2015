#include "Game.h"

Game::Game(unsigned int pScreenWidth, unsigned int pScreenHeight, float pLogicalScreenWidth,
                float charAncho, float charAlto, Stage* pStage, string OponentSide)
{
    this->ScreenWidth = pScreenWidth;
    this->ScreenHeight = pScreenHeight;
    this->logicalScreenWidth = pLogicalScreenWidth;
    this->stage = pStage;
    this->oponentSide = OponentSide;
    scorpion = new MKCharacter(INITIAL_POSITION_X, INITIAL_POSITION_Y, charAncho, charAlto, 2);
    this->gameView = new GameView(ScreenWidth, ScreenHeight, scorpion, stage, oponentSide);
    this->gameController = new GameController();

}

Game::~Game()
{
    delete scorpion;
    delete gameView;
    delete gameController;
}

void Game::GameLoop()
{
    while (gameController->getEvent()->type != SDL_QUIT)
    {
        gameController->checkEvent();
        gameView->startRender();
        gameView->Render();
        gameController->update(scorpion, stage->getLayers());
        gameView->endRender();
    }
}
