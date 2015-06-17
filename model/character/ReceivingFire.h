/*
 * ReceivingFire.h
 *
 *  Created on: 30/05/2015
 *      Author: her
 */

#ifndef RECEIVINGFIRE_H_
#define RECEIVINGFIRE_H_

#include "CharacterState.h"

class ReceivingFire: public CharacterState {
public:
	ReceivingFire();
	virtual ~ReceivingFire();
	string getName();
	float getWidth();
	void refreshTimer(MKCharacter* character);
private:
	int timer;
};

#endif /* RECEIVINGFIRE_H_ */
