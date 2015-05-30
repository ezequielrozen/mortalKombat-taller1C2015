#include "EventController.h"
#include "InputController.h" //Esto esta solamanete por el metodo setCharacterSide que se deberia qitar de aca
extern logger* Mylog;

EventController::EventController() {

}

EventController::~EventController() {
	// TODO Auto-generated destructor stub
}
void EventController::Void(){}

void EventController::setCharacterToMove(MKCharacter* character) {
	this->characterToMove = character;
}

void EventController::moveRight(){
//	cout << "moveRight : " << this->characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
	this->characterToMove->update(MoveRight);
}

void EventController::moveRightRelease(){
//	cout << "moveRightRelease : " << this->characterToMove->getName() << endl;
	this->characterToMove->update(MoveRightRelease);
}

void EventController::moveLeft(){
//	cout << "moveLeft : " << this->characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: hacia la Izquierda", ERROR_LEVEL_INFO);
	this->characterToMove->update(MoveLeft);
}

void EventController::moveLeftRelease(){
//	cout << "moveLeftRelease : " << this->characterToMove->getName() << endl;
	this->characterToMove->update(MoveLeftRelease);
}

void EventController::moveUp(){
//	cout << "moveUp : " << this->characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
	this->characterToMove->update(Jump);
}

void EventController::moveDown(){
//	cout << "moveDown : " << this->characterToMovegetName() << endl;
	Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
	this->characterToMove->update(Duck);
}

void EventController::moveDownRelease(){
//	cout << "moveDownRelease : " << this->this->characterToMoveToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Levantandose", ERROR_LEVEL_INFO);
	this->characterToMove->update(DuckRelease);
}

void EventController::highKick(){
//	cout << "highKick : " << this->characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Patada alta", ERROR_LEVEL_INFO);
	this->characterToMove->update(HighKick);
}

void EventController::lowKick(){
//	cout << "lowKick : " << this->characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
	this->characterToMove->update(LowKick);
}

void EventController::highPunch(){
//	cout << "highPunch : " << this->characterToMovegetName() << endl;
	Mylog->Log("movimiento del personaje: Golpe de puño alto.", ERROR_LEVEL_INFO);
	this->characterToMove->update(HighPunch);
}

void EventController::lowPunch(){
//	cout << "lowPunch : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: Golpe de puño bajo.", ERROR_LEVEL_INFO);
	this->characterToMove->update(LowPunch);
}

void EventController::shoot(){
//	cout << "shoot : " << this->characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
	this->characterToMove->update(WeaponHit);
}

void EventController::block(){
//	cout << "block : " << this->characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
	this->characterToMove->update(Block);
}

void EventController::blockRelease(){
//	cout << "blockRelease : " << this->characterToMove->getName() << endl;
	this->characterToMove->update(BlockRelease);
}

void EventController::duckPunch(){
//	cout << "duckPunch : " << this->characterToMove->getName() << endl;
//	this->characterToMove->update(DuckPunch);
}
