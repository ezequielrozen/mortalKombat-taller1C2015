#include "GameView.h"

GameView::GameView(GameSetup* pGameSetup, MKCharacter* character)
{
    gameSetup = pGameSetup;
    scorpion = character;
 	this->LoadSprites();   
}


GameView::~GameView(void)
{
	delete scorpionWalk;
}

void GameView::Draw() {

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
	scorpionWalk = new MKSprite(gameSetup->getRenderer(),"data/scorpionWalk.png", scorpion->getX(),scorpion->getY(), 120,187, 9);
    scorpionStance = new MKSprite(gameSetup->getRenderer(),"data/scorpionStance.png", scorpion->getX(),scorpion->getY(), 120,187, 7);	
}

