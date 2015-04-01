#include "Game.h"

Game::Game(int pScreenWidth, int pScreenHeight)
{
    ScreenWidth = pScreenWidth;
    ScreenHeight = pScreenHeight;
    scorpion = new MKCharacter(INITIAL_POSITION_X, INITIAL_POSITION_Y);
    gameView = new GameView(ScreenWidth, ScreenHeight, scorpion);
    gameController = new GameController();
}


Game::~Game(void)
{
    delete scorpion;
    delete gameView;
    delete gameController;
}


void Game::GameLoop(void)
{
    while (gameController->getEvent()->type != SDL_QUIT)
    {
        gameController->checkEvent();
        gameView->startRender();
        gameView->Render();
        scorpion->Update(gameController);
        gameView->endRender();
    }
}
