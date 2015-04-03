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
<<<<<<< HEAD
        scorpionStance->Play(0, 6, 50);
=======
        scorpionStance->Play(0, 6, 33);
>>>>>>> 69e022887687e3c3b27ba8e939e277f6b0b2b4ec
        scorpionStance->setX(scorpion->getX());
        scorpionStance->Draw();
    }
    else if (scorpion->getMovement() == "WALKINGRIGHT") {
<<<<<<< HEAD
        scorpionWalk->Play(0, 8, 50);
=======
        scorpionWalk->Play(0, 8, 33);
>>>>>>> 69e022887687e3c3b27ba8e939e277f6b0b2b4ec
        scorpionWalk->setX(scorpion->getX());
        scorpionWalk->Draw();
    }
    else if (scorpion->getMovement() == "WALKINGLEFT") {
<<<<<<< HEAD
        scorpionWalk->WalkBack(8, 0,50);
        scorpionWalk->setX(scorpion->getX());
        scorpionWalk->Draw();
    };
=======
        scorpionWalk->WalkBack(8, 0, 33);
        scorpionWalk->setX(scorpion->getX());
        scorpionWalk->Draw();
    }
    else if (scorpion->getMovement() == "JUMPUP") {
        	scorpionJump->Play(0, 3, 300);
        	scorpionJump->setX(scorpion->getX());
        	scorpionJump->setY(scorpion->getY());
        	scorpionJump->Draw();
    	};;

>>>>>>> 69e022887687e3c3b27ba8e939e277f6b0b2b4ec
}

void GameView::LoadSprites() {
	scorpionWalk = new CharacterSprite(this->renderer,"data/scorpionWalk.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    scorpionStance = new CharacterSprite(this->renderer,"data/scorpionStance.png", scorpion->getX(),scorpion->getY(), 120,187, 7);
    scorpionJump = new CharacterSprite(this->renderer,"data/scorpionJump.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    layerSprite = new LayerSprite(this->renderer,"data/stage.png",700,500);
}

void GameView::startRender() {
    SDL_RenderClear(renderer);
}   

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

