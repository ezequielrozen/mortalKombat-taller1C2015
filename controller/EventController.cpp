/*
 * EventController.cpp
 *
 *  Created on: 16/05/2015
 *      Author: her
 */

#include "EventController.h"
#include "InputController.h" //Esto esta solamanete por el metodo setCharacterSide que se deberia qitar de aca
extern logger* Mylog;

static bool vibrating;
EventController::EventController() {
}

EventController::~EventController() {
	// TODO Auto-generated destructor stub
}

void EventController::moveRight(MKCharacter* characterToMove, MKCharacter* character2){
//	cout << "moveRight" << endl;
	Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
	characterToMove->update(MoveRight);
}

void EventController::moveRightRelease(MKCharacter* characterToMove, MKCharacter* character2){
	characterToMove->update(MoveRightRelease);
}

void EventController::moveLeft(MKCharacter* characterToMove, MKCharacter* character2){
	Mylog->Log("movimiento del personaje: hacia la Izquierda", ERROR_LEVEL_INFO);
	characterToMove->update(MoveLeft);
}

void EventController::moveLeftRelease(MKCharacter* characterToMove, MKCharacter* character2){
	characterToMove->update(MoveLeftRelease);
}

void EventController::moveUp(MKCharacter* characterToMove, MKCharacter* character2){
	Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
	characterToMove->update(Jump);
}

void EventController::moveDown(MKCharacter* character, MKCharacter* character2){
//	cout << "moveDown" << endl;
	Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
	character->update(Duck);
}

void EventController::moveDownRelease(MKCharacter* characterToMove, MKCharacter* character2){
	Mylog->Log("movimiento del personaje: Levantandose", ERROR_LEVEL_INFO);
	characterToMove->update(DuckRelease);
}

void EventController::highKick(MKCharacter* character, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: Patada alta", ERROR_LEVEL_INFO);
	character->update(HighKick);
}

void EventController::lowKick(MKCharacter* character, MKCharacter* character2){
	Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
	character->update(LowKick);
}

void EventController::highPunch(MKCharacter* character, MKCharacter* character2){
	Mylog->Log("movimiento del personaje: Golpe de puño alto.", ERROR_LEVEL_INFO);
	character->update(HighPunch);
}

void EventController::lowPunch(MKCharacter* character, MKCharacter* character2){
//	cout << "lowPunch" << endl;
	Mylog->Log("movimiento del personaje: Golpe de puño bajo.", ERROR_LEVEL_INFO);
	character->update(LowPunch);
}

void EventController::shoot(MKCharacter* character, MKCharacter* character2){
	Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
	character->update(Shoot);
}

void EventController::block(MKCharacter* character, MKCharacter* character2){
//	cout << "block" << endl;
	Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
	character->update(Block);
}

void EventController::blockRelease(MKCharacter* character, MKCharacter* character2){
	character->update(BlockRelease);
}






void EventController::dizzy(MKCharacter* character, MKCharacter* character2){
//	character->update(MoveRight);
}
void EventController::beingHit(MKCharacter* character, MKCharacter* character2){
//	character->update(MoveRight);
}
void EventController::winner(MKCharacter* character, MKCharacter* character2)
{
//	character->update(MoveRight);
}



void EventController::setVibrating(bool vibratingFlag) {
	vibrating = vibratingFlag;
}

