#include "MKMain.h"

MKMain::MKMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
    ScreenWidth = passed_ScreenWidth;
    ScreenHeight = passed_ScreenHeight;
    quit = false;
    gameSetup = new GameSetup(&quit, ScreenWidth, ScreenHeight);
    scorpion = new MKCharacter(gameSetup);
}


MKMain::~MKMain(void)
{
    delete gameSetup;
    delete scorpion;
}


void MKMain::GameLoop(void)
{
    while (!quit && gameSetup->getMainEvent()->type != SDL_QUIT)
    {
        gameSetup->Begin();
        scorpion->Draw();
        scorpion->Update();
        gameSetup->End();
    }
}
