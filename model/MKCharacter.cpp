#include "MKCharacter.h"
#include "../controller/InputController.h"
#include "character/CharacterStance.h"

MKCharacter::MKCharacter(float initialPosX, float ancho, float alto, int z_index, int pCharacterNumber, string name) {

	this->weapon = new Weapon(ancho*0.97, alto*0.36);
	this->weaponFire = new Fire(ancho*0.97, alto*0.36);
	this->weaponIce = new WeaponIce(ancho*0.97, alto*0.2);
	this->state = new CharacterStance();
	this->z_index = z_index;
	posX = initialPosX;
	auxPosX = initialPosX;
	this->name = name;
	this->alto = alto;
	this->ancho = ancho;

	this->stagePosX = ((Util::getInstance()->getLogicalStageWidth()-Util::getInstance()->getLogicalWindowWidth())/2) + initialPosX;

	step = 0.00651 * Util::getInstance()->getLogicalWindowWidth();

	jumpTime = 0;
	ascending = false;


	this->life = FULL_LIFE;

	this->characterNumber = pCharacterNumber;

	this->weaponFireUsed = false;
	this->fatalityEnable = false;

	this->practiceMode = false;

}

MKCharacter::~MKCharacter(void) {
	delete this->state;
	delete this->weapon;
	delete this->weaponFire;
	delete this->weaponIce;
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

	this->updateOverPassing();

	this->state->refreshTimer(this);

	if (this->state->getName() == "WeaponHitting" && this->state->startThrowing() && !this->weapon->isActive()) {
		throwWeapon();
	}
	this->weapon->update();


	if (this->state->startThrowingFire() && !this->weaponFire->isActive()) {
		throwWeaponFire();
	}
	this->weaponFire->update();

	if (this->state->getName() == "WeaponHittingIce" && this->state->startThrowing() && !this->weaponIce->isActive() && !this->weaponIce->getImpactingWeaponIce()) {
		throwWeaponIce();
	}
	this->weaponIce->update();

	if (this->state->getName() == "FlyHitting")
	{

		//cuando cambia de lado seteo checkSide en false porq sino se da vuelta el sprite.
		if (this->state->getSideWhenInit() == 'l') {
			//if (this->getCharacterSide() == 'r'){
				this->state->setCheckSide(false);
			//}
			this->posX += step*2;
		}else
		{
			if (this->getCharacterSide() == 'l'){
				this->state->setCheckSide(false);
			}
			this->posX -= step*2;
		}
	}
}


Throwable *MKCharacter::getWeapon() {
	return this->weapon;
}

void MKCharacter::throwWeapon() {
		this->weapon->throwWeapon(this->posX, this->posY + this->getHeight() * 0.2,this->getCharacterSide());
}

Throwable *MKCharacter::getWeaponFire() {
	return this->weaponFire;
}

void MKCharacter::throwWeaponFire() {
	if (!this->weaponFireUsed && this->fatalityEnable){
		if (this->getCharacterSide() == 'l') {
			this->weaponFire->throwWeapon(this->posX + (this->getWidth() * 1.3),this->posY+(this->alto*0.35) ,this->getCharacterSide());
		}else
		{
			this->weaponFire->throwWeapon(this->posX - (this->getWidth()*0.7),this->posY+(this->alto*0.45) ,this->getCharacterSide());
		}
		this->weaponFireUsed = true;
	}
}

Throwable *MKCharacter::getWeaponIce() {
	return this->weaponIce;
}

void MKCharacter::throwWeaponIce() {

	if (this->getCharacterSide() == 'l') {
		this->weaponIce->throwWeapon(this->posX + (this->getWidth() * 0.85), this->posY,this->getCharacterSide());
	}else
	{
		this->weaponIce->throwWeapon(this->posX-(this->getWidth()*0.67), this->posY,this->getCharacterSide());
	}
}

void MKCharacter::setFatalityEnable(bool state){
	fatalityEnable = state;
}

bool MKCharacter::getFatalityEnable(){
	return fatalityEnable;
}

void MKCharacter::updateOverPassing() {
	if (this->isBeingOverPassedRight()) {
		if (this->getX() <= stopX)
			this->moveRightFaster();
		else
			this->update(OverPassedFinished);
	}
	else if (this->isBeingOverPassedLeft()) {
		if (this->getX() >= stopX)
			this->moveLeftFaster();
		else
			this->update(OverPassedFinished);
	}
}

void MKCharacter::moveRight() {
	//Verifico que no se vaya de la pantalla por derecha
	if ((posX + step + getWidth() < Util::getInstance()->getLogicalWindowWidth())) {
		posX = posX + step;
		stagePosX = stagePosX + step;
	}
}

void MKCharacter::moveRightFaster() {
	//Verifico que no se vaya de la pantalla por derecha
	if ((posX + step + getWidth() < Util::getInstance()->getLogicalWindowWidth())) {
		posX = posX + step;
		stagePosX = stagePosX + step;
	}
}

void MKCharacter::moveLeftFaster() {
	//Verifico que no se vaya de la pantalla por izquierda
	if ((posX - step + getWidth() > getWidth())) {
		posX = posX - step;
		stagePosX = stagePosX - step;
	}
}

void MKCharacter::moveLeft() {
	//Verifico que no se vaya de la pantalla por izquierda
	if ((posX - step + getWidth() > getWidth())) {
		posX = posX - step;
		stagePosX = stagePosX - step;
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

void MKCharacter::setX(double X) {
	posX = X;
}

double MKCharacter::getStagePosX() {
	return stagePosX;
}

void MKCharacter::increaseStagePosX() {
	this->stagePosX = this->stagePosX + step;
}

void MKCharacter::decreaseStagePosX() {
	this->stagePosX = this->stagePosX - step;
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
	if (this->state->getName() == "Dizzy"){
		this->update(ReceiveFire);
	}else
	{
		if (!this->practiceMode)
			this->life -= force;

		if (this->state->getName() != "ReceivingIce") {
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
		} else
		{
			InputController::setVibrating(true);
		}
		Mylog->Log("Personaje (PONERLE NOMBRE) recibe golpe", ERROR_LEVEL_INFO); //FALTA: nombre, vida restada, vida restante.
		if (this->life <= 0) {
			this->life = 0;//marcar fin de juego. Preferentemente donde se invoca esta función (control de colisión y golpe)
		}
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

void MKCharacter::moveForced(double x) {
	//if ((x + this->getStateWidth() < Util::getInstance()->getLogicalStageWidth() * 0.4) && x > this->getWidth())
				posX = x;
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

bool MKCharacter::isReceivingHit() {
	this->state->isReceivingHit();
}

bool MKCharacter::isBeingOverPassedRight() {
	return this->state->isBeingOverPassedRight();
}

bool MKCharacter::isBeingOverPassedLeft() {
	return this->state->isBeingOverPassedLeft();
}

string MKCharacter::getState() {
	return this->state->getName();
}
char MKCharacter::getStateSideWhenInit() {
	return this->state->getSideWhenInit();
}
float MKCharacter::getStateWidth() {
	return (this->ancho)*(this->state->getWidth());
}

float MKCharacter::getStateHeight() {
	return (this->alto)*(this->state->getHeight());
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
		return (this->getWeapon()->isImpact() || this->getWeaponFire()->isImpact() || this->getWeaponIce()->isImpact());
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


void MKCharacter::disableImpact() {
	this->state->disableImpact(this);
}

void MKCharacter::setStopX(float x) {
	this->stopX = x;
}

void MKCharacter::setFinalPosX(float oponentPosX, float oponentWidth) {
	float pos = 0;
	if (this->state->getFinalPosX() == 0){

		if (this->getCharacterSide() == 'l') {

			pos = oponentPosX + (oponentWidth*1.08);

			//cout << this->posX << " - " << pos<< " - " << pos + getWidth()<< " - " <<Util::getInstance()->getLogicalWindowWidth() << endl;

			//Verifico que no se vaya de la pantalla por derecha
			if ((pos + getWidth() <= Util::getInstance()->getLogicalWindowWidth())) {
				this->state->setFinalPosX(pos);
			}
			else
			{
				this->setState(new CharacterStance());
			}

		}else
		{
			pos = oponentPosX - (getWidth() *1.08);

			//cout << this->posX << " - " << pos<< " - " << pos + getWidth()<< " - " <<Util::getInstance()->getLogicalWindowWidth() << endl;

			//Verifico que no se vaya de la pantalla por izquierda
			if (pos >= 0) {
				this->state->setFinalPosX(pos);
			}
			else
			{
				this->setState(new CharacterStance());
			}

		}
	}
}

void MKCharacter::setFinalPosXAfterFlyHitting(float oponentPosX, float oponentWidth) {
	float pos = 0;
	if (this->state->getFinalPosX() == 0){

		if (this->getCharacterSide() == 'r') {

			pos = oponentPosX + (oponentWidth*2);

			//cout << oponentPosX << " -- " << pos << " - " << endl;

			//Verifico que no se vaya de la pantalla por derecha
			if ((pos + getWidth() <= Util::getInstance()->getLogicalWindowWidth())) {
				this->posX = pos;
				this->setState(new CharacterStance());
			}
			else
			{
				this->setState(new CharacterStance());
			}

		}else
		{
			pos = oponentPosX - (getWidth() *2);

			//cout << oponentPosX << " - " << pos << " - " << endl;

			//Verifico que no se vaya de la pantalla por izquierda
			if (pos >= 0) {
				this->posX = pos;
				this->setState(new CharacterStance());
			}
			else
			{
				this->setState(new CharacterStance());
			}

		}
	}
}

int MKCharacter::getCharacterNumber() {
	return this->characterNumber;
}

void MKCharacter::enablePracticeMode() {
	this->practiceMode = true;
}

void MKCharacter::disablePracticeMode() {
	this->practiceMode = false;
}

void MKCharacter::setWeaponFireUsed(bool isFiring) {
	this->weaponFireUsed = isFiring;
}

bool MKCharacter::getWeaponFireStatus() {
	return this->weaponFireUsed;
}
