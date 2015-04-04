#include "GameView.h"

GameView::GameView(float ScreenWidth, float ScreenHeight, MKCharacter* character, Stage* pStage) {
    this->window = NULL;
    this->window = SDL_CreateWindow("Mortal Kombat", 100, 100, (int) ScreenWidth, (int) ScreenHeight, SDL_WINDOW_SHOWN);

    if (this->window == NULL) {

        std::cout << "Window couldn't be created" << std::endl;
    }

    this->renderer = NULL;
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_TARGETTEXTURE);

    this->screenWidth = ScreenWidth;
    this->screenHeight = ScreenHeight;

    this->stage = pStage;
    this->scorpion = character;
 	this->LoadSprites();

  /*  std::list<Layer*>::iterator it = this->stage->getLayers()->begin();
    for(it; it != this->stage->getLayers()->end(); it++) {
        if ((*it)->getWidth() > ANCHOVENTANAL)
            (*it)->setWidth((*it)->getWidth() * layerSprite->getCropWidthRelation());
    }*/
 }

GameView::~GameView() {
    delete scorpionJump;
    delete layerSprite;
	delete scorpionWalk;
    delete scorpionStance;
    delete scorpionSideJump;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void GameView::Render() {
    float leftBorders [2];
    int i = 0;
    std::list<Layer*>::iterator it = this->stage->getLayers()->begin();
    for(it; it != this->stage->getLayers()->end(); it++) {
        //layerSprite->update((*it)->getLeft_border());
        //layerSprite->Draw();
        leftBorders[i] = (*it)->getLeft_border();
        i++;
    }

    layerSprite->update(leftBorders[0]);
    layerSprite->Draw();

    layerSpriteSubway->update(leftBorders[1]);
    layerSpriteSubway->Draw();

    CharacterSprite* sprite;

    if (scorpion->isJumping() && scorpion->getJumpMovement() == "NONE") {
        sprite = scorpionJump;
        sprite->Play(300);
    }
    else if (scorpion->isJumping() && scorpion->getJumpMovement() == "RIGHT") {
        sprite = scorpionSideJump;
        sprite->Play(50);
    }
    else if (scorpion->isJumping() && scorpion->getJumpMovement() == "LEFT") {
        sprite = scorpionSideJump;
        sprite->PlayBack(50);
    }
    else if (scorpion->getMovement() == "NONE") {
        sprite = scorpionStance;
        sprite->Play(100);
    }
    else if (scorpion->getMovement() == "RIGHT") {
        sprite = scorpionWalk;
        sprite->Play(100);
    }
    else if (scorpion->getMovement() == "LEFT") {
        sprite = scorpionWalk;
        sprite->PlayBack(100);
    };

    sprite->setX(scorpion->getX());
    sprite->setY(scorpion->getY());
    sprite->Draw();

}

void GameView::LoadSprites() {
	scorpionWalk = new CharacterSprite(this->renderer,"data/scorpionWalk.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    scorpionStance = new CharacterSprite(this->renderer,"data/scorpionStance.png", scorpion->getX(),scorpion->getY(), 120,187, 7);
    scorpionJump = new CharacterSprite(this->renderer,"data/scorpionJump.png", scorpion->getX(),scorpion->getY(), 120,187, 9);

    scorpionSideJump = new CharacterSprite(this->renderer, "data/scorpionSideJump.png", scorpion->getX(), scorpion->getY(), 120, 187, 8);
    layerSprite = new LayerSprite(this->renderer,"data/stage2.jpg",screenWidth,screenHeight);
    layerSpriteSubway = new LayerSprite(this->renderer,"data/152.png",screenWidth,screenHeight);

}

void GameView::startRender() {
    SDL_RenderClear(renderer);
}   

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

