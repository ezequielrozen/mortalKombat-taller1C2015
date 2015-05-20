/*
 * EventController.cpp
 *
 *  Created on: 16/05/2015
 *      Author: her
 */

#include "EventController.h"
#include "InputController.h" //Esto esta solamanete por el metodo setCharacterSide que se deberia qitar de aca
extern logger* Mylog;

EventController::EventController() {

}

EventController::~EventController() {
	// TODO Auto-generated destructor stub
}
void EventController::Void(){}

void EventController::moveRight(MKCharacter* characterToMove, MKCharacter* character2){
//	cout << "moveRight : " << characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
	characterToMove->update(MoveRight);
}

void EventController::moveRightRelease(MKCharacter* characterToMove, MKCharacter* character2){
//	cout << "moveRightRelease : " << characterToMove->getName() << endl;
	characterToMove->update(MoveRightRelease);
}

void EventController::moveLeft(MKCharacter* characterToMove, MKCharacter* character2){
//	cout << "moveLeft : " << characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: hacia la Izquierda", ERROR_LEVEL_INFO);
	characterToMove->update(MoveLeft);
}

void EventController::moveLeftRelease(MKCharacter* characterToMove, MKCharacter* character2){
//	cout << "moveLeftRelease : " << characterToMove->getName() << endl;
	characterToMove->update(MoveLeftRelease);
}

void EventController::moveUp(MKCharacter* characterToMove, MKCharacter* character2){
//	cout << "moveUp : " << characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
	characterToMove->update(Jump);
}

void EventController::moveDown(MKCharacter* character, MKCharacter* character2){
//	cout << "moveDown : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
	character->update(Duck);
}

void EventController::moveDownRelease(MKCharacter* characterToMove, MKCharacter* character2){
//	cout << "moveDownRelease : " << characterToMove->getName() << endl;
	Mylog->Log("movimiento del personaje: Levantandose", ERROR_LEVEL_INFO);
	characterToMove->update(DuckRelease);
}

void EventController::highKick(MKCharacter* character, MKCharacter* character2){
//	cout << "highKick : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: Patada alta", ERROR_LEVEL_INFO);
	character->update(HighKick);
}

void EventController::lowKick(MKCharacter* character, MKCharacter* character2){
//	cout << "lowKick : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
//	character->update(LowKick);
}

void EventController::highPunch(MKCharacter* character, MKCharacter* character2){
//	cout << "highPunch : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: Golpe de puño alto.", ERROR_LEVEL_INFO);
	character->update(HighPunch);
}

void EventController::lowPunch(MKCharacter* character, MKCharacter* character2){
//	cout << "lowPunch : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: Golpe de puño bajo.", ERROR_LEVEL_INFO);
//	character->update(LowPunch);
}

void EventController::shoot(MKCharacter* character, MKCharacter* character2){
//	cout << "shoot : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
//	character->update(Shoot);
}

void EventController::block(MKCharacter* character, MKCharacter* character2){
//	cout << "block : " << character->getName() << endl;
	Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
	character->update(Block);
}

void EventController::blockRelease(MKCharacter* character, MKCharacter* character2){
//	cout << "blockRelease : " << character->getName() << endl;
	character->update(BlockRelease);
}

void EventController::duckPunch(MKCharacter* character, MKCharacter* character2){
//	cout << "duckPunch : " << character->getName() << endl;
//	character->update(DuckPunch);
}
