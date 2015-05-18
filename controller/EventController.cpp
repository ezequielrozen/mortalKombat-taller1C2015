/*
 * EventController.cpp
 *
 *  Created on: 16/05/2015
 *      Author: her
 */

#include "EventController.h"
#include "InputController.h" //Esto esta solamanete por el metodo setCharacterSide que se deberia qitar de aca
extern logger* Mylog;

//TODO: Elimnar todas estas var al terminar
static int timer = SDL_GetTicks();
static int timerChar2;
static int hitTimer;
static int hitTimerChar2;
static int hitTimerRaidenShootCheck = SDL_GetTicks();
static bool raidenShootTimeOutCompleted = true;
static int hitTimerScorpionShootCheck = SDL_GetTicks();
static bool scorpionShootTimeOutCompleted = true;
static string previousKey;
static string previousKeyChar2;
static bool vibrating;
EventController::EventController() {
	//TODO: Eliminar todas estas var al terminar
//    previousKey = "";
//    timer = SDL_GetTicks();
//    hitTimerRaidenShootCheck = SDL_GetTicks();
//    raidenShootTimeOutCompleted = true;
//    hitTimerScorpionShootCheck = SDL_GetTicks();
//    scorpionShootTimeOutCompleted = true;

}

EventController::~EventController() {
	// TODO Auto-generated destructor stub
}

void EventController::moveRight(MKCharacter* characterToMove, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
	characterToMove->setMovement("RIGHT");
	vibrating = false;
	previousKey = "RIGHT";
	setCharacterSide(characterToMove, character2);
	timer = SDL_GetTicks();

	characterToMove->update(MoveRight);
}

void EventController::moveLeft(MKCharacter* characterToMove, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
	characterToMove->setMovement("LEFT");
	previousKey = "LEFT";
	setCharacterSide(characterToMove, character2);
	timer = SDL_GetTicks();

	characterToMove->update(MoveLeft);

}

void EventController::moveUp(MKCharacter* characterToMove, MKCharacter* character2)
{
	if (previousKey == "UP"){
		Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
		characterToMove->setJump(true);
		setCharacterSide(characterToMove, character2);
	}
	previousKey = "UP";

	characterToMove->update(Jump);
}

void EventController::moveDown(MKCharacter* character, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
	character->setMovement("DUCK");
	previousKey = "DUCK";
	timer = SDL_GetTicks();

//	character->update(MoveDown);
}
void EventController::highKick(MKCharacter* character, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: Patada alta", ERROR_LEVEL_INFO);
	character->setHit("KICK");
	previousKey = "highKick";
	character->setIsHiting(true);
	hitTimer = SDL_GetTicks();

//	character->update(HighKick);
}

void EventController::lowKick(MKCharacter* character, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
	character->setHit("KICKDOWN");
	previousKey = "lowKick";
	character->setIsHiting(true);
	hitTimer = SDL_GetTicks();

//	character->update(LowKick);
}

void EventController::highPunch(MKCharacter* character, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: Golpe de puño alto.", ERROR_LEVEL_INFO);
	character->setHit("PUNCH");
	previousKey = "highPunch";
	character->setIsHiting(true);
	hitTimer = SDL_GetTicks();

//	character->update(HighPunch);
}
void EventController::lowPunch(MKCharacter* character, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: Golpe de puño bajo.", ERROR_LEVEL_INFO);
	character->setHit("PUNCHDOWN");
	previousKey = "lowPunch";
	character->setIsHiting(true);
	hitTimer = SDL_GetTicks();

//	character->update(LowPunch);

}
void EventController::shoot(MKCharacter* character, MKCharacter* character2)
{
	if ((SDL_GetTicks() < 150 + hitTimerScorpionShootCheck) || scorpionShootTimeOutCompleted){
			Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
			character->setHit("SHOOT");
			previousKey = "shoot";
			character->setIsHiting(true);
			hitTimer = SDL_GetTicks();
			scorpionShootTimeOutCompleted = false;
			if (hitTimerScorpionShootCheck == 0)
				hitTimerScorpionShootCheck = SDL_GetTicks();
	}else
	{
		hitTimerScorpionShootCheck = 0;
	}

	//character->update(Shoot);
}
void EventController::block(MKCharacter* character, MKCharacter* character2)
{
	Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
	character->setHit("DEFENSE");
	previousKey = "block";
	hitTimer = SDL_GetTicks();

//	character->update(Block);
}

void EventController::dizzy(MKCharacter* character, MKCharacter* character2)
{
//	character->update(MoveRight);
}
void EventController::beingHit(MKCharacter* character, MKCharacter* character2)
{
//	character->update(MoveRight);
}
void EventController::winner(MKCharacter* character, MKCharacter* character2)
{
//	character->update(MoveRight);
}



void EventController::setVibrating(bool vibratingFlag) {
	vibrating = vibratingFlag;
}


