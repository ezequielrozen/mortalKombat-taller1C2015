#include "CharacterState.h"
#include "../MKCharacter.h"
void CharacterState::update(MKCharacter *character, Events anEvent) {

}

void CharacterState::setState(MKCharacter *character, CharacterState *state) {
    character->setState(state);
}

bool CharacterState::isMovingLeft() {
	return false;
}

bool CharacterState::isMovingRight() {
	return false;
}

bool CharacterState::isJumping() {
	return false;
}

bool CharacterState::isHitting() {
	return false;
}

bool CharacterState::isBlocking() {
	return false;
}

bool CharacterState::isDucking() {
	return false;
}

bool CharacterState::isReceivingHit() {
	return false;
}

float CharacterState::getWidth() {
	return 1;
}

float CharacterState::getJumpLevel() {
	return 1;
}

string CharacterState::getName() {
	return "asd";
}

void CharacterState::refreshTimer(MKCharacter* character) {
	
}

bool CharacterState::impact() {
	return false;
}


bool CharacterState::startThrowing() {
	return false;
}

bool CharacterState::startThrowingFire() {
	return false;
}

float CharacterState::getHeight() {
	return 1;
}

bool CharacterState::isBeingOverPassedRight() {
	return false;
}

bool CharacterState::isBeingOverPassedLeft() {
	return false;
}

void CharacterState::disableImpact(MKCharacter* character) {
	
}

void CharacterState::setFinalPosX(float finalX)
{
}

float CharacterState::getFinalPosX()
{
	return 0;
}

char CharacterState::getSideWhenInit()
{
	return ' ';
}

void CharacterState::setTimer(int time){

}
int CharacterState::getTimer(){
	return 0;
}

void CharacterState::setMovingLeft(bool state){

}
void CharacterState::setMovingRight(bool state){

}