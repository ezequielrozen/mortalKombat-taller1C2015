#include "Game.h"

Game::Game(int pScreenWidth, int pScreenHeight)
{
    ScreenWidth = pScreenWidth;
    ScreenHeight = pScreenHeight;
    quit = false;
    gameSetup = new GameSetup(&quit, ScreenWidth, ScreenHeight);
    scorpion = new MKCharacter(gameSetup, INITIAL_POSITION_X, INITIAL_POSITION_Y);
    gameView = new GameView(gameSetup, scorpion);
    gameController = new GameController(gameSetup);
}


Game::~Game(void)
{
    delete gameSetup;
    delete scorpion;
    delete gameView;
    delete gameController;
}


void Game::GameLoop(void)
{
    while (!quit && gameSetup->getMainEvent()->type != SDL_QUIT)
    {
        gameSetup->Begin();
        gameView->Draw();
        scorpion->Update(gameController);
        gameSetup->End();
    }
}
