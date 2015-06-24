#include "EventController.h"
#include "InputController.h" //Esto esta solamanete por el metodo setCharacterSide que se deberia qitar de aca
extern logger* Mylog;

EventController::EventController(std::vector<Events>* combo1, std::vector<Events>* combo2,std::vector<Events>* combo3,
	std::vector<Events>* combo4,std::vector<Events>* combo5,std::vector<Events>* combo6,std::vector<Events>* fatality) {
	for (int i = 0; i < 2; i++) {
		commands[i].upPressed = false;
		commands[i].downPressed = false;
		commands[i].leftPressed = false;
		commands[i].rightPressed = false;
		commands[i].highPunchPressed = false;
		commands[i].lowPunchPressed = false;
		commands[i].highKickPressed = false;
		commands[i].lowKickPressed = false;
		commands[i].blockPressed = false;
		commands[i].weaponThrowPressed = false;
	}
	this->comboManager = new ComboManager();
	this->comboManager->loadCombos(combo1, combo2,combo3,combo4,combo5,combo6,fatality);
	this->comboManagerChar2 = new ComboManager();
	this->comboManagerChar2->loadCombos(combo1, combo2,combo3,combo4,combo5,combo6,fatality);
}

EventController::~EventController() {
	delete this->comboManager;
	delete this->comboManagerChar2;
}
void EventController::Void(){}

void EventController::setCharacterToMove(MKCharacter* character) {
	this->characterToMove = character;
}

void EventController::moveRight(int n){
//	cout << "moveRight : " << this->characterToMove->getName() << endl;
	if (!commands[n].rightPressed) {
		Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(MoveRight, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(MoveRight, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		//cout << "RIGHT PRESSED" << endl;
		commands[n].rightPressed = true;
	}
}

void EventController::moveRightRelease(int n){
//	cout << "moveRightRelease : " << this->characterToMove->getName() << endl;
	this->characterToMove->update(MoveRightRelease);
	commands[n].rightPressed = false;
	commands[n].upPressed = false;
}

void EventController::moveLeft(int n){
//	cout << "moveLeft : " << this->characterToMove->getName() << endl;
	if (!commands[n].leftPressed) {
		Mylog->Log("movimiento del personaje: hacia la Izquierda", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(MoveLeft, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(MoveLeft, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		//cout << "LEFT PRESSED" << endl;
		commands[n].leftPressed = true;
	}
}

void EventController::moveLeftRelease(int n){
//	cout << "moveLeftRelease : " << this->characterToMove->getName() << endl;
	this->characterToMove->update(MoveLeftRelease);
	commands[n].leftPressed = false;
	commands[n].upPressed = false;
}

void EventController::moveUp(int n){
//	cout << "moveUp : " << this->characterToMove->getName() << endl;
	if (!commands[n].upPressed) {
		Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(Jump, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(Jump, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		//cout << "UP PRESSED" << endl;
		commands[n].upPressed = true;
	}
}

void EventController::moveUpRelease(int n) {
	commands[n].upPressed = false;
}

void EventController::moveDown(int n){
//	cout << "moveDown : " << this->characterToMovegetName() << endl;
	if (!commands[n].downPressed) {
		Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(Duck, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(Duck, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		//cout << "DOWN PRESSED" << endl;
		commands[n].downPressed = true;
	}
}

void EventController::moveDownRelease(int n){
//	cout << "moveDownRelease : " << this->this->characterToMoveToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Levantandose", ERROR_LEVEL_INFO);
	this->characterToMove->update(DuckRelease);
	commands[n].downPressed = false;
}

void EventController::highKick(int n){
//	cout << "highKick : " << this->characterToMove->getName() << endl;
	if (!commands[n].highKickPressed) {
		Mylog->Log("movimiento del personaje: Patada alta", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(HighKick, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(HighKick, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		commands[n].highKickPressed = true;
	}
}

void EventController::lowKick(int n){
//	cout << "lowKick : " << this->characterToMove->getName() << endl;
	if (!commands[n].lowKickPressed) {
		Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(LowKick, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(LowKick, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		commands[n].lowKickPressed = true;
	}
}

void EventController::highPunch(int n){
//	cout << "highPunch : " << this->characterToMovegetName() << endl;
	if (!commands[n].highPunchPressed) {
		Mylog->Log("movimiento del personaje: Golpe de puño alto.", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(HighPunch, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(HighPunch, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		commands[n].highPunchPressed = true;
		//cout << "HIGGH PUNCH APRETADO" << endl;
	}
}

void EventController::lowPunch(int n){
//	cout << "lowPunch : " << character->getName() << endl;
	if (!commands[n].lowPunchPressed) {
		Mylog->Log("movimiento del personaje: Golpe de puño bajo.", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(LowPunch, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(LowPunch, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		commands[n].lowPunchPressed = true;
	}
}

void EventController::shoot(int n){
//	cout << "shoot : " << this->characterToMove->getName() << endl;
	if (!commands[n].weaponThrowPressed) {
		Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(WeaponHit, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(WeaponHit, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		commands[n].weaponThrowPressed = true;
	}

//	this->characterToMove->update(WeaponHitIce);
}

void EventController::block(int n){
//	cout << "block : " << this->characterToMove->getName() << endl;
	if (!commands[n].blockPressed) {
		Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
		if (this->characterToMove->getName() == "scorpion") {
			this->characterToMove->update(this->comboManager->checkCombo(Block, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		} else {
			this->characterToMove->update(this->comboManagerChar2->checkCombo(Block, this->characterToMove->getCharacterSide(), this->characterToMove->getName()));
		}
		commands[n].blockPressed = true;
	}
}

void EventController::blockRelease(int n){
//	cout << "blockRelease : " << this->characterToMove->getName() << endl;
	commands[n].blockPressed = false;
	this->characterToMove->update(BlockRelease);
}

void EventController::duckPunch() {
	//cout << "duckPunch : " << this->characterToMove->getName() << endl;
//	this->characterToMove->update(DuckPunch);
//	this->characterToMove->update(FatalityHit);
//	this->characterToMove->update(Teleportation);
	this->characterToMove->update(FlyHit);
}



void EventController::weaponRelease(int n) {
	commands[n].weaponThrowPressed = false;
}

void EventController::lowKickRelease(int n) {
	commands[n].lowKickPressed = false;
}

void EventController::highKickRelease(int n) {
	commands[n].highKickPressed = false;
}

void EventController::lowPunchRelease(int n) {
	commands[n].lowPunchPressed = false;
}

void EventController::highPunchRelease(int n) {
	commands[n].highPunchPressed = false;
}

ComboManager *EventController::getComboManager() {
	return this->comboManager;
}
