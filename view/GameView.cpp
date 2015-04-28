#include "GameView.h"

GameView::GameView(float ScreenWidth, float ScreenHeight, MKCharacter* character, MKCharacter* character2, Stage* pStage, string OponentSide) {

	oponentSide = OponentSide;
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
    this->raiden = character2;
 	this->LoadSprites();

    layerCount = this->stage->getLayers()->size();
    layerSprites = new LayerSprite*[layerCount-1];

    std::list<Layer*>::iterator it = this->stage->getLayers()->begin();

    int i = 0;

    // We load the sprites and put them into an array
    for(it; it != this->stage->getLayers()->end(); it++) {
        layerSprites[i] = new LayerSprite(this->renderer,(*it)->getPath(),screenWidth,screenHeight, (*it)->getWidth());
        //cout << "paths; " << (*it)->getPath() << endl;

        i++;
    }
}

GameView::~GameView() {
    delete scorpionJump;
	delete scorpionWalk;
    delete scorpionStance;
    delete scorpionSideJump;
    for (int i = 1 ; i < layerCount ; i++) {
        delete layerSprites[i];
    }
    delete layerSprites;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void GameView::Render() {
    int i = 0;
    bool painted = false;
    // We render the layers' sprites iterating through the layerSprites' array
    std::list<Layer*>::iterator it = this->stage->getLayers()->begin();
    for(it; it != this->stage->getLayers()->end(); it++) {
        if (scorpion->getZ_index() == i+1) {
            this->runCharacter();
            layerSprites[i]->update((*it)->getLeft_border());
            layerSprites[i]->Draw();
            painted = true;
        } else {
            layerSprites[i]->update((*it)->getLeft_border());
            layerSprites[i]->Draw();
        }
        i++;
    }
    if (!painted) {
        this->runCharacter();
    }
}

void GameView::LoadSprites() {
	scorpionWalk = new CharacterSprite(this->renderer, scorpion->getWalk(), scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 9, oponentSide, false);
    scorpionStance = new CharacterSprite(this->renderer, scorpion->getStance(), scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 7, oponentSide, false);
    scorpionJump = new CharacterSprite(this->renderer, scorpion->getJump(), scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 9, oponentSide, false);
    scorpionSideJump = new CharacterSprite(this->renderer, scorpion->getSideJump(), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 8, oponentSide, false);
    scorpionDuck = new CharacterSprite(this->renderer, scorpion->getDuck(), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, true);
    raidenWalk = new CharacterSprite(this->renderer, raiden->getWalk(), raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 9, (oponentSide == "RIGHT") ? "LEFT" : "RIGHT" , false);
    raidenStance = new CharacterSprite(this->renderer, raiden->getStance(), raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 7, (oponentSide == "RIGHT") ? "LEFT" : "RIGHT", false);
    raidenJump = new CharacterSprite(this->renderer, raiden->getJump(), raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 9, (oponentSide == "RIGHT") ? "LEFT" : "RIGHT", false);
    raidenSideJump = new CharacterSprite(this->renderer, raiden->getSideJump(), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 8, (oponentSide == "RIGHT") ? "LEFT" : "RIGHT", false);
    raidenDuck = new CharacterSprite(this->renderer, raiden->getDuck(), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, true);
}

void GameView::startRender() {
    SDL_RenderClear(renderer);
}

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

void GameView::runCharacter() {
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
    }
    else if (scorpion->getMovement() == "DUCK") {
        sprite = scorpionDuck;
        //sprite->setRepeatLastSprite(false);
        sprite->Play(100);
    };

    CharacterSprite* sprite2;

    if (raiden->isJumping() && raiden->getJumpMovement() == "NONE") {
        sprite2 = scorpionJump;
        sprite2->Play(300);
    }
    else if (raiden->isJumping() && raiden->getJumpMovement() == "RIGHT") {
        sprite2 = raidenSideJump;
        sprite2->Play(50);
    }
    else if (raiden->isJumping() && raiden->getJumpMovement() == "LEFT") {
        sprite2 = raidenSideJump;
        sprite2->PlayBack(50);
    }
    else if (raiden->getMovement() == "NONE") {
        sprite2 = raidenStance;
        sprite2->Play(100);
    }
    else if (raiden->getMovement() == "RIGHT") {
        sprite2 = raidenWalk;
        sprite2->Play(100);
    }
    else if (raiden->getMovement() == "LEFT") {
        sprite2 = raidenWalk;
        sprite2->PlayBack(100);
    }
    else if (scorpion->getMovement() == "DUCK") {
        sprite = scorpionDuck;
        sprite->Play(100);
    };

    if(scorpion->getX() < raiden->getX()){
        sprite->switchSide('r');
        sprite2->switchSide('l');
    }else{
        sprite->switchSide('l');
        sprite2->switchSide('r');
    }

    sprite->setX(scorpion->getX());
    sprite->setY(scorpion->getY());
    sprite->Draw();

    sprite2->setX(raiden->getX());
    sprite2->setY(raiden->getY());
    sprite2->Draw();
}

