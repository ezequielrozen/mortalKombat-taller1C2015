#include "MKCharacter.h"
#include "../controller/InputController.h"
#include "character/CharacterStance.h"

MKCharacter::MKCharacter(float initialPosX, float ancho, float alto, int z_index, int pCharacterNumber, string name) {

	this->weapon = new Weapon(ancho*0.97, alto*0.36);
	this->state = new CharacterStance();
	this->z_index = z_index;
	posX = initialPosX;
	auxPosX = initialPosX;
	this->name = name;
	this->alto = alto;
	this->ancho = ancho;

	step = 0.042 * this->ancho;

	jumpTime = 0;
	ascending = false;


	this->life = FULL_LIFE;

	this->characterNumber = pCharacterNumber;

}

MKCharacter::~MKCharacter(void) {
	delete this->state;
	delete this->weapon;
}

void MKCharacter::move() {
	if (isMovingRight()) {
		this->moveRight();
	} else if (isMovingLeft()) {
		this->moveLeft();
	}
}

void MKCharacter::characterUpdate() {

	if (this->state->isJumping()) {

		this->moveUp();
	}

	this->state->refreshTimer(this);
	if (this->state->startThrowing() && !this->weapon->isActive()) {
		throwWeapon();
		cout << "ARROJO EL ARMA" << endl;
	}

	this->weapon->update();

}

void MKCharacter::moveRight() {
	//Verifico que no se vaya de la pantalla por derecha
	if ((posX + step + getWidth() < Util::getInstance()->getLogicalWindowWidth())) {
		posX = posX + step;
	}
}

void MKCharacter::moveLeft() {
	//Verifico que no se vaya de la pantalla por izquierda
	if ((posX - step + getWidth() > getWidth())) {
		posX = posX - step;
	}
}

void MKCharacter::moveUp() {

	double lastPosY = stageFloor - this->getVelY()*jumpTime - (this->getAccY()*pow(jumpTime,2))/2;

	jumpTime = jumpTime + 0.015;

	posY = stageFloor - this->getVelY()*jumpTime - (this->getAccY()*pow(jumpTime,2))/2;

	ascending = lastPosY > posY;
	
	if (posY <= 0) {
		double time1;
		double time2;

		time1 = (this->getVelY() + sqrt(pow(this->getVelY(),2)-4*(-this->getAccY()/2)*stageFloor))/(-this->getAccY());
		time2 = (this->getVelY() - sqrt(pow(this->getVelY(),2)-4*(-this->getAccY()/2)*stageFloor))/(-this->getAccY());

		jumpTime = fmax(time1, time2);
	}
	
	if (posY > stageFloor) {
		//this->setJump(false);
		update(JumpFinished);

		posY = stageFloor;
		jumpTime = 0;
	}
}

float MKCharacter::getWidth() {
	return this->ancho;
}

float MKCharacter::getHeight() {
	return this->alto;
}

double MKCharacter::getX() {
	return posX;
}

double MKCharacter::getY() {
	return posY;
}

int MKCharacter::getZ_index() {
	return this->z_index;
}


int MKCharacter::getLife() {
	return this->life;
}

void MKCharacter::setLife(int life) {
	if (life > 0)
		this->life = life;
	else
		this->life = 100;
}

char* MKCharacter::getFileMovement(const char* moveName){
	std::list<Util::charactersFile*>::iterator it = Util::getInstance()->getCharacterMovements()->begin();

	for(it; it != Util::getInstance()->getCharacterMovements()->end(); it++) {

		if (strcmp(((*it)->movementName),moveName) == 0 && (*it)->characterNumber == this->characterNumber)		{
			return ((*it)->fileName);
		}
	}
}

bool MKCharacter::isAlive() {

	return this->life > 0;
//	return true;

}
void MKCharacter::receiveBlow(int force, char direction) {
	extern logger* Mylog;
	this->life -= force;

	if (force <= 10) {
		this->update(ReceiveHit);
	}
	else if (force > 10 && force <= 15) {
		this->update(ReceiveDuckingPunch);
		InputController::setVibrating(true);
	}
	else {
		this->update(ReceiveDuckingPunch);
		InputController::setVibrating(true);
	}

	Mylog->Log("Personaje (PONERLE NOMBRE) recibe golpe", ERROR_LEVEL_INFO); //FALTA: nombre, vida restada, vida restante.
	if (this->life <= 0) {
		this->life = 0;//marcar fin de juego. Preferentemente donde se invoca esta función (control de colisión y golpe)
	}
}

string MKCharacter::getName() {
	return this->name;
}

void MKCharacter::setName(string aName) {
	this->name = aName;
}

void MKCharacter::setStageFloor(double d) {
	this->stageFloor = d;

}

void MKCharacter::setPosY(double d) {
	this->posY = d;
}

void MKCharacter::setCharacterSide(char side) {
	this->characterSide = side;
}

char MKCharacter::getCharacterSide() {
	return this->characterSide;
}

bool MKCharacter::isAscending() {
	return this->ascending;
}

void MKCharacter::setInitialPosition(double d) {
	posX = d;
	auxPosX = d;
}

void MKCharacter::setState(CharacterState *state) {
	delete this->state;
	this->state = state;
}

void MKCharacter::update(Events aEvent) {
	this->state->update(this, aEvent);
}

bool MKCharacter::isMovingLeft() {
	this->state->isMovingLeft();
}

bool MKCharacter::isMovingRight() {
	this->state->isMovingRight();
}


bool MKCharacter::isJumping() {
	this->state->isJumping();
}

string MKCharacter::getState() {
	if (this->weapon->isActive()) {
		return "WeaponHitting";
	}
	return this->state->getName();
}

float MKCharacter::getStateWidth() {
	return (this->ancho)*(this->state->getWidth());
}

bool MKCharacter::isHitting() {
	return this->state->isHitting();
}

bool MKCharacter::isDucking() {
	return this->state->isDucking();
}

bool MKCharacter::isBlocking() {
	return this->state->isBlocking();
}

bool MKCharacter::impacts() {
	if (this->state->isHitting()) {
		return this->state->impact();
	}
	else {
		this->getWeapon()->isImpact();
	}
}

double MKCharacter::getYMax() {
	return (stageFloor - (this->alto)*1.20)/(this->state->getJumpLevel());
}

double MKCharacter::getVelY() {
	return (6.4 * (this->alto))*(this->state->getJumpLevel());
}

double MKCharacter::getAccY() {
	return (-2*(this->getYMax()-stageFloor+this->getVelY()*0.5))/(pow(0.5,2));
}

Weapon *MKCharacter::getWeapon() {
	return this->weapon;
}

void MKCharacter::throwWeapon() {
	//	this->weapon->throwWeapon(this->posX + this->getWidth(),this->posY +  this->getHeight() * 0.2 /* AL 80% DE LA ALTURA DEL PERSONAJE, USAR CTE*/, this->getCharacterSide());
	if (this->getCharacterSide() == 'l') {
		this->weapon->throwWeapon(this->posX + this->getWidth(),
								  this->posY + this->getHeight() * 0.2,
								  this->getCharacterSide());
	}
	else {
		this->weapon->throwWeapon(this->posX - this->weapon->getWidth(),
								this->posY + this->getHeight()*0.2,
								this->getCharacterSide());
	}
}

float MKCharacter::getStateHeight() {
	return (this->alto)*(this->state->getHeight());
}

