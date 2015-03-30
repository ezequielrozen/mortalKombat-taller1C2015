#include "MKCharacter.h"

MKCharacter::MKCharacter(GameSetup* passed_SDL_Setup, int initialPosX, int initialPosY)
{
	gameSetup = passed_SDL_Setup;

	//tamaño del png = 87*136

	timeCheck = SDL_GetTicks();

	posX = initialPosX;
	posY = initialPosY;

	movement = "NONE";

}

MKCharacter::~MKCharacter(void)
{
}

void MKCharacter::Update(GameController* gameController)
{
	if (gameController->getCommand() == "RIGHT") {
		//this->moveRight();
		movement = "WALKINGRIGHT";
	}
	else if (gameController->getCommand() == "LEFT") {
		//this->moveLeft();
		movement = "WALKINGLEFT";
	}
	else {
		movement = "NONE";
	}

	if (timeCheck + 5 < SDL_GetTicks()) {
		if (movement == "WALKINGRIGHT") {
			this->moveRight();
		}
		else if (movement == "WALKINGLEFT") {
			this->moveLeft();
		}
		timeCheck = SDL_GetTicks();
	}

}

void MKCharacter::moveRight() {

    //Verifico que no se vaya de la pantalla por derecha
    
    if(( posX + 5 + getWidth() < gameSetup->getScreenWidth() ) )
    {
    	posX = posX + 5;
    }

}

void MKCharacter::moveLeft() {
	//Verifico que no se vaya de la pantalla por izquierda
	
	if(( posX - 5 + getWidth() > getWidth() ) )
	{
		posX = posX - 5;
	}

}

int MKCharacter::getWidth(){
	return CHARACTER_WIDHT;
}

int MKCharacter::getX() {
	return posX;
}

int MKCharacter::getY() {
	return posY;
}

string MKCharacter::getMovement() {
	return movement;
}
