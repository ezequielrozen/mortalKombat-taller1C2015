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

    std::list<Layer*>::iterator it = this->stage->getLayers()->begin();
    for(it; it != this->stage->getLayers()->end(); it++) {
        (*it)->setWidth(ScreenWidth * layerSprite->getCropWidthRelation());
    }
 }

GameView::~GameView() {
    delete scorpionJump;
    delete layerSprite;
	delete scorpionWalk;
    delete scorpionStance;
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


    if (scorpion->isJumping()) {
            scorpionJump->Play(0, 3, 500);
            scorpionJump->setX(scorpion->getX());
            scorpionJump->setY(scorpion->getY());
            scorpionJump->Draw();
    }
    else if (scorpion->getMovement() == "NONE") {
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
	scorpionWalk = new CharacterSprite(this->renderer,"data/scorpionWalk.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    scorpionStance = new CharacterSprite(this->renderer,"data/scorpionStance.png", scorpion->getX(),scorpion->getY(), 120,187, 7);
    scorpionJump = new CharacterSprite(this->renderer,"data/scorpionJump.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    layerSprite = new LayerSprite(this->renderer,"data/stage2.jpg",screenWidth,screenHeight);
    layerSpriteSubway = new LayerSprite(this->renderer,"data/tthesubway.png",screenWidth,screenHeight);

}

void GameView::startRender() {
    SDL_RenderClear(renderer);
}   

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

