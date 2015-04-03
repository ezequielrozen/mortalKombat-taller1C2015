#include "Game.h"

Game::Game(int pScreenWidth, int pScreenHeight, float charAncho, float charAlto)
{
    ScreenWidth = pScreenWidth;
    ScreenHeight = pScreenHeight;
    scorpion = new MKCharacter(INITIAL_POSITION_X, INITIAL_POSITION_Y,
                     charAncho,  charAlto);
    layer = new Layer(617,1);
    gameView = new GameView(ScreenWidth, ScreenHeight, scorpion, layer);
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
        gameController->update(scorpion, layer);
        gameView->endRender();
    }
}
