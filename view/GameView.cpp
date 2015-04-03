#include <unistd.h>
#include "GameView.h"

GameView::GameView(int ScreenWidth, int ScreenHeight, MKCharacter* character, Layer* layer)
{
    window = NULL;
    window = SDL_CreateWindow("Mortal Kombat", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

    if (window == NULL) {

        std::cout << "Window couldn't be created" << std::endl;
    }

    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    this->layer = layer;
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
      layerSprite->Draw();
      layerSprite->update(layer->getLeft_border());
    if (scorpion->getMovement() == "NONE") {
        scorpionStance->Play(0, 6, 50);
        scorpionStance->setX(scorpion->getX());
        scorpionStance->Draw();
    }
    else if (scorpion->getMovement() == "WALKINGRIGHT") {
        scorpionWalk->Play(0, 8, 50);
        scorpionWalk->setX(scorpion->getX());
        scorpionWalk->Draw();
    }
    else if (scorpion->getMovement() == "WALKINGLEFT") {
        scorpionWalk->WalkBack(8, 0,50);
        scorpionWalk->setX(scorpion->getX());
        scorpionWalk->Draw();
    };
}

void GameView::LoadSprites() {
	scorpionWalk = new CharacterSprite(this->renderer,"data/scorpionWalk.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    scorpionStance = new CharacterSprite(this->renderer,"data/scorpionStance.png", scorpion->getX(),scorpion->getY(), 120,187, 7);
    layerSprite = new LayerSprite(this->renderer,"data/stage.png",700,500);
}

void GameView::startRender() {
    SDL_RenderClear(renderer);
}   

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

