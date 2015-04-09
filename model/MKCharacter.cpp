#include "MKCharacter.h"

MKCharacter::MKCharacter(int initialPosX, int initialPosY, float ancho, float alto, int z_index)
{

	//tamaño del png = 87*136
	//timeCheck = SDL_GetTicks();

	this->z_index = z_index;
	posX = initialPosX;
	posY = initialPosY;

	this->alto = alto;
	this->ancho = ancho;

	posY = 200;
	velY = SPEED;
	accY = ACCELERATION;

	movement = "NONE";
	jumpMovement = "NONE";

	jumping = false;

}

MKCharacter::~MKCharacter(void)
{
}

void MKCharacter::Update()
{

	//if (timeCheck + MOVEMENTDELAY < SDL_GetTicks()) {
		if (movement == "RIGHT") {
			this->moveRight();
		}
		else if (movement == "LEFT") {
			this->moveLeft();
		}

		//timeCheck = SDL_GetTicks();
	//}
}

void MKCharacter::UpdateJump() {
	
	if(this->isJumping()) {
		this->moveUp();
	}
}

void MKCharacter::moveRight() {

    //Verifico que no se vaya de la pantalla por derecha
    
    if(( posX + 5 + getWidth() < SCREEN_WIDTH ) )
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

void MKCharacter::moveUp() {

	if (posY > 40 && posY <= 201)
	{
		float time = 0.003;

		//cout << "PosY:" << posY << "  Vel: " << velY << "   Time: " << time << " movement: " << movement << endl;

		velY = velY - accY * time;

		posY = posY - velY;
	}

	if (velY <= (SPEED*0.04 - SPEED)) {
		posY = 200;
		velY = SPEED;
		this->setJump(false);
	}
}

int MKCharacter::getWidth(){
	return CHARACTER_WIDTH;
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

void MKCharacter::setMovement(string newMovement) {
	
	if (!this->isJumping()) {
		this->movement = newMovement;
	}
}

void MKCharacter::setJump(bool jump) {
	this->jumping = jump;

	this->setJumpMovement(this->movement);
}

bool MKCharacter::isJumping() {
	return this->jumping;
}

string MKCharacter::getJumpMovement() {
	return this->jumpMovement;
}

void MKCharacter::setJumpMovement(string jumpMove) {
	this->jumpMovement = jumpMove;
}

int MKCharacter::getZ_index() {
	return this->z_index;
}
