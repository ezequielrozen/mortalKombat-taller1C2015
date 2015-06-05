/*
 * TeleportationDoing.h
 *
 *  Created on: 05/06/2015
 *      Author: her
 */

#ifndef TELEPORTATIONDOING_H_
#define TELEPORTATIONDOING_H_

#include "CharacterState.h"

class TeleportationDoing: public CharacterState {
public:
	TeleportationDoing();
	virtual ~TeleportationDoing();
	string getName();
	void refreshTimer(MKCharacter* character);
	void setFinalPosX(float finalX);
	float getFinalPosX();
//	float getWidth();
//	float getHeight();
	void update(MKCharacter* character, Events aEvent);
private:
	int timer;
	float finalPosX;
};

#endif /* TELEPORTATIONDOING_H_ */
