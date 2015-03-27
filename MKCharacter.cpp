#include "MKCharacter.h"

MKCharacter::MKCharacter(GameSetup* passed_SDL_Setup)
{
	gameSetup = passed_SDL_Setup;

	//tamaño del png = 87*136
	scorpion = new MKSprite(gameSetup->getRenderer(),"data/scorpionWalk.png", 200,200, 120,187);
	scorpion->SetUpAnimation(9,1);

	timeCheck = SDL_GetTicks();
	stopAnimation = false;

}

MKCharacter::~MKCharacter(void)
{
	delete scorpion;
}

void MKCharacter::Draw()
{
	scorpion->DrawSteady();
}

void MKCharacter::Update()
{
	if (timeCheck + 1 < SDL_GetTicks()) {
		if (gameSetup->getMainEvent()->type == SDL_KEYDOWN)
		{
			if (gameSetup->getMainEvent()->key.keysym.sym == SDLK_RIGHT)
			{
				this->moveRight();
				scorpion->Walk(0, 8, 33);
			}
			else if (gameSetup->getMainEvent()->key.keysym.sym == SDLK_LEFT)
			{
				this->moveLeft();
				scorpion->WalkBack(8, 0, 33);
			}
		}
		timeCheck = SDL_GetTicks();
	}
}

void MKCharacter::moveRight() {
	scorpion->setX(scorpion->getX()+1);
}

void MKCharacter::moveLeft() {
	scorpion->setX(scorpion->getX()-1);
}
