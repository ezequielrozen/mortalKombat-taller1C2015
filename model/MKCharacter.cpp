#include "MKCharacter.h"

MKCharacter::MKCharacter(float initialPosX, float initialPosY, float ancho, float alto, int z_index)
{

	//tamaño del png = 87*136
	//timeCheck = SDL_GetTicks();

	this->z_index = z_index;
	posX = initialPosX;
	posY = initialPosY;

	step = 0.00714*Util::getInstance()->getLogicalWindowWidth();

	this->alto = alto;
	this->ancho = ancho;

	velY = 0.04285*Util::getInstance()->getLogicalWindowWidth();
	accY = 1.2285*Util::getInstance()->getLogicalWindowWidth();;

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
    
    if(( posX + step + getWidth() < Util::getInstance()->getLogicalWindowWidth() ) )
    {
    	posX = posX + step;
    }

}

void MKCharacter::moveLeft() {
	//Verifico que no se vaya de la pantalla por izquierda
	
	if(( posX - step + getWidth() > getWidth() ) )
	{
		posX = posX - step;
	}

}

void MKCharacter::moveUp() {

	if (posY > (0.0571*Util::getInstance()->getLogicalWindowWidth()) && posY <= (0.2871*Util::getInstance()->getLogicalWindowWidth()))
	{
		float time = 0.003;

		//cout << "PosY:" << posY << "  Vel: " << velY << "   Time: " << time << " movement: " << movement << endl;

		velY = velY - accY * time;

		posY = posY - velY;
	}

	if (velY <= (0.04285*Util::getInstance()->getLogicalWindowWidth()*0.04 - 0.04285*Util::getInstance()->getLogicalWindowWidth())) {
		posY = INITIAL_POSITION_Y;
		velY = 0.04285*Util::getInstance()->getLogicalWindowWidth();
		this->setJump(false);
	}
}

//PASAR A FLOAT
float MKCharacter::getWidth(){
	return this->ancho;
}

//PASAR A FLOAT
float MKCharacter::getHeight(){
	return this->alto;
}

double MKCharacter::getX() {
	return posX;
}

double MKCharacter::getY() {
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
