#include "MKCharacter.h"
//#include "../controller/GameController.h"
#include "../controller/InputController.h"
#include "character/CharacterStance.h"

MKCharacter::MKCharacter(float initialPosX, float ancho, float alto, int z_index, int pCharacterNumber, string name) {

	this->weapon = new Weapon(alto / 4, alto / 4);

	this->state = new CharacterStance();
	this->z_index = z_index;
	posX = initialPosX;
	auxPosX = initialPosX;
	this->name = name;
	this->alto = alto;
	this->ancho = ancho;

	this->hitWidth = ancho;
	this->hitDelay = 0;

	step = 0.042 * this->ancho;

	jumpTime = 0;
	//Parte de la ecuacion de tiro vertical. El 0.5 sale de que el salto total dura 1seg, por lo cual al punto maximo del salto llega en 0.5seg
	//accY = (-2*(yMax-stageFloor+velY*0.5))/(pow(0.5,2));
	//Si el salto esta en etapa ascendente o descendente.
	ascending = false;

	movement = "NONE";
	jumpMovement = "NONE";
	hitMovement = "NONE";
	this->hitReception = "NONE";
	jumping = false;

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

	if (this->hitReceptionDelay == 0) {
		this->setHitReception("NONE");
	}

	if (this->hitReception != "NONE") {
		this->hitReceptionDelay = this->hitReceptionDelay - 1;
	}

	this->state->refreshTimer(this);
	if (this->state->startThrowing() && !this->weapon->isActive()) {
		throwWeapon();
		cout << "ARROJO EL ARMA" << endl;
	}
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

void MKCharacter::setHit(string newHit) {

	double stanceWidth = (this->name == "scorpion") ? 76 : 73;

	double spriteWidth = 0;
	int delay = 0;

	this->hitMovement = newHit;

	if (newHit == "NONE" || newHit =="WINNER") {
		this->setHitWidth(this->getWidth());

		if ((this->getCharacterSide() == 'r') && (this->getIsHiting())) {
			this->posX = this->auxPosX;
		}
	}
	else
	{
		if (newHit == "BEINGHIT") {
			if (this->getHitDelay() <= 0) {
				this->setHitDelay(3);
			}
		}
		else
		{
			if (newHit == "KICK") {
				spriteWidth = (this->name == "scorpion") ? 143 : 142;
				delay = 4;
			}

			if (newHit == "KICKDOWN") {
				spriteWidth = (this->name == "scorpion") ? 136 : 146;
				delay = 4;
			}

			if (newHit == "PUNCH") {
				spriteWidth = (this->name == "scorpion") ? 118 : 124;
				delay = 2;
			}

			if (newHit == "PUNCHUP") {
				spriteWidth = (this->name == "scorpion") ? 115 : 105;
				delay = 3;
			}

			if (newHit == "SHOOT") {
				spriteWidth = (this->name == "scorpion") ? 120 : 81;
				delay = 3;
			}

			if (newHit == "PUNCHJUMPLEFT" || newHit == "PUNCHJUMPRIGHT") {
				spriteWidth = stanceWidth;
				delay = 0;
			}

			if ((newHit == "KICK") || (newHit == "KICKDOWN")  || (newHit == "PUNCH")  || (newHit == "PUNCHUP") || (newHit == "SHOOT") ||
				(newHit == "PUNCHJUMPLEFT") || (newHit == "PUNCHJUMPRIGHT")){

				if (this->getHitDelay() <= 0) {
					this->setHitDelay(delay);
				}

				if ((this->getCharacterSide() == 'r') && (!this->getIsHiting())) {
					this->auxPosX = this->posX;

					this->posX = this->posX - ((this->getWidth()*(spriteWidth/stanceWidth)) - this->getWidth());
				}

				this->setHitWidth(this->getWidth()*spriteWidth/stanceWidth);
			}
		}
	}
}

string MKCharacter::getHit() {
	return this->hitMovement;
}
/*
bool MKCharacter::isJumping() {
	return this->jumping;
}
*/

bool MKCharacter::getIsHiting() {
	return this->isHiting;
}

void MKCharacter::setIsHiting(bool state) {
	this->isHiting = state;
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
	if (force >= 15) {
//		GameController::setVibrating(true);
		this->update(ReceiveHit);
		InputController::setVibrating(true);
		if (direction != 0)
		{
			cout << direction << endl;
			(direction == 'l') ? this->setMovement("LEFT") : this->setMovement("RIGHT");
		}
	}
	else {
		this->update(ReceiveHit);
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

void MKCharacter::setHitWidth(float width) {
	this->hitWidth = width;
}

float MKCharacter::getHitWidth() {
	return this->hitWidth;
}

void MKCharacter::setHitDelay(int delay) {
	this->hitDelay = delay;
}

int MKCharacter::getHitDelay() {
	return this->hitDelay;
}

void MKCharacter::setCharacterSide(char side) {
	this->characterSide = side;
}

char MKCharacter::getCharacterSide() {
	return this->characterSide;
}
string MKCharacter::getHitReception() {
	return this->hitReception;
}

void MKCharacter::setHitReception(string reception) {
	this->hitReception = reception;

	//PERDON POR HARDCODEAR ESTOS NUMEROS. ESTOY BUSCANDO UNA ALTERNATIVA. ATTE: GONZALO

	if (reception == "BEINGHIT" || reception == "BEINGHITDOWN") {
		this->hitReceptionDelay = 20;
	}
	else if (reception == "FALLING") {
		this->hitReceptionDelay = 80;
	}
	else if (reception == "NONE") {
		this->hitReceptionDelay = 0;
	}
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
	return this->state->impact();
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
	this->weapon->throwWeapon(this->posX,this->posY +  this->getHeight() * 0.2 /* AL 80% DE LA ALTURA DEL PERSONAJE, USAR CTE*/, this->getCharacterSide());
}