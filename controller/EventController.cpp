#include "EventController.h"
#include "InputController.h" //Esto esta solamanete por el metodo setCharacterSide que se deberia qitar de aca
extern logger* Mylog;

EventController::EventController(std::vector<Events>* combo1, std::vector<Events>* combo2, std::vector<Events>* fatality) {
	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	highPunchPressed = false;
	lowPunchPressed = false;
	highKickPressed = false;
	lowKickPressed = false;
	blockPressed = false;
	weaponThrowPressed = false;
	this->comboManager = new ComboManager();
	this->comboManager->loadCombos(combo1, combo2, fatality);
}

EventController::~EventController() {
	// TODO Auto-generated destructor stub
}
void EventController::Void(){}

void EventController::setCharacterToMove(MKCharacter* character) {
	this->characterToMove = character;
}

void EventController::moveRight(int n){
//	cout << "moveRight : " << this->characterToMove->getName() << endl;
	if (!rightPressed) {
		Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);

		this->characterToMove->update(this->comboManager->checkCombo(MoveRight, this->characterToMove->getCharacterSide()));
		cout << "RIGHT PRESSED" << endl;
		rightPressed = true;
	}
}

void EventController::moveRightRelease(int n){
//	cout << "moveRightRelease : " << this->characterToMove->getName() << endl;
	this->characterToMove->update(MoveRightRelease);
	rightPressed = false;
	upPressed = false;
}

void EventController::moveLeft(int n){
//	cout << "moveLeft : " << this->characterToMove->getName() << endl;
	if (!leftPressed) {
		Mylog->Log("movimiento del personaje: hacia la Izquierda", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(MoveLeft, this->characterToMove->getCharacterSide()));
		cout << "LEFT PRESSED" << endl;
		leftPressed = true;
	}
}

void EventController::moveLeftRelease(int n){
//	cout << "moveLeftRelease : " << this->characterToMove->getName() << endl;
	this->characterToMove->update(MoveLeftRelease);
	leftPressed = false;
	upPressed = false;
}

void EventController::moveUp(int n){
//	cout << "moveUp : " << this->characterToMove->getName() << endl;
	if (!upPressed) {
		Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(Jump, this->characterToMove->getCharacterSide()));
		cout << "UP PRESSED" << endl;
		upPressed = true;
	}
}

void EventController::moveUpRelease(int n) {
	upPressed = false;
}

void EventController::moveDown(int n){
//	cout << "moveDown : " << this->characterToMovegetName() << endl;
	if (!downPressed) {
		Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(Duck, this->characterToMove->getCharacterSide()));
		cout << "DOWN PRESSED" << endl;
		downPressed = true;
	}
}

void EventController::moveDownRelease(int n){
//	cout << "moveDownRelease : " << this->this->characterToMoveToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Levantandose", ERROR_LEVEL_INFO);
	this->characterToMove->update(DuckRelease);
	downPressed = false;
}

void EventController::highKick(){
//	cout << "highKick : " << this->characterToMove->getName() << endl;
	if (!highKickPressed) {
		Mylog->Log("movimiento del personaje: Patada alta", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(HighKick, this->characterToMove->getCharacterSide()));
		highKickPressed = true;
	}
}

void EventController::lowKick(int n){
//	cout << "lowKick : " << this->characterToMove->getName() << endl;
	if (!lowKickPressed) {
		Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(LowKick, this->characterToMove->getCharacterSide()));
		lowKickPressed = true;
	}
}

void EventController::highPunch(){
//	cout << "highPunch : " << this->characterToMovegetName() << endl;
	if (!highPunchPressed) {
		Mylog->Log("movimiento del personaje: Golpe de puño alto.", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(HighPunch, this->characterToMove->getCharacterSide()));
		highPunchPressed = true;
		cout << "HIGGH PUNCH APRETADO" << endl;
	}
}

void EventController::lowPunch(){
//	cout << "lowPunch : " << character->getName() << endl;
	if (!lowPunchPressed) {
		Mylog->Log("movimiento del personaje: Golpe de puño bajo.", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(LowPunch, this->characterToMove->getCharacterSide()));
		lowPunchPressed = true;
	}
}

void EventController::shoot(){
//	cout << "shoot : " << this->characterToMove->getName() << endl;
	if (!weaponThrowPressed) {
		Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(WeaponHit, this->characterToMove->getCharacterSide()));
		weaponThrowPressed = true;
	}

//	this->characterToMove->update(WeaponHitIce);
}

void EventController::block(){
//	cout << "block : " << this->characterToMove->getName() << endl;
	if (!blockPressed) {
		Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
		this->characterToMove->update(this->comboManager->checkCombo(Block, this->characterToMove->getCharacterSide()));
		blockPressed = true;
	}
}

void EventController::blockRelease(){
//	cout << "blockRelease : " << this->characterToMove->getName() << endl;
	blockPressed = false;
	this->characterToMove->update(BlockRelease);
}

void EventController::duckPunch() {
//	cout << "duckPunch : " << this->characterToMove->getName() << endl;
//	this->characterToMove->update(DuckPunch);
	this->characterToMove->update(FatalityHit);
//	this->characterToMove->update(Teleportation);
}



void EventController::weaponRelease() {
	weaponThrowPressed = false;
}

void EventController::lowKickRelease(int n) {
	lowKickPressed = false;
}

void EventController::highKickRelease(int n) {
	highKickPressed = false;
}

void EventController::lowPunchRelease(int n) {
	lowPunchPressed = false;
}

void EventController::highPunchRelease(int n) {
	highPunchPressed = false;
}

ComboManager *EventController::getComboManager() {
	return this->comboManager;
}
