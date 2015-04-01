#include "GameView.h"

GameView::GameView(int ScreenWidth, int ScreenHeight, MKCharacter* character)
{
    window = NULL;
    window = SDL_CreateWindow("Mortal Kombat", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

    if (window == NULL) {

        std::cout << "Window couldn't be created" << std::endl;
    }

    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    scorpion = character;
 	this->LoadSprites();   
}

GameView::~GameView(void)
{
	delete scorpionWalk;
    delete scorpionStance;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void GameView::Render() {

    if (scorpion->getMovement() == "NONE") {
        scorpionStance->Play(0, 6, 33);
        scorpionStance->setX(scorpion->getX());
        scorpionStance->Draw();
    }
    else if (scorpion->getMovement() == "WALKINGRIGHT") {
        scorpionWalk->Play(0, 8, 33);
        scorpionWalk->setX(scorpion->getX());
        scorpionWalk->Draw();
    }
    else if (scorpion->getMovement() == "WALKINGLEFT") {
        scorpionWalk->WalkBack(8, 0, 33);
        scorpionWalk->setX(scorpion->getX());
        scorpionWalk->Draw();
    };

}

void GameView::LoadSprites() {
	scorpionWalk = new MKSprite(this->renderer,"data/scorpionWalk.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    scorpionStance = new MKSprite(this->renderer,"data/scorpionStance.png", scorpion->getX(),scorpion->getY(), 120,187, 7);	
}

void GameView::startRender() {
    SDL_RenderClear(renderer);
}   

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

