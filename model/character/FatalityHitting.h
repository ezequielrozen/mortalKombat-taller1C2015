/*
 * FatalityHitting.h
 *
 *  Created on: 30/05/2015
 *      Author: her
 */

#ifndef FATALITYHITTING_H_
#define FATALITYHITTING_H_

#include "CharacterState.h"

class FatalityHitting: public CharacterState {
public:
	FatalityHitting();
	virtual ~FatalityHitting();
	string getName();
	void refreshTimer(MKCharacter* character);
	bool startThrowing();
	float getWidth();
	float getHeight();
private:
	int timer;
};

#endif /* FATALITYHITTING_H_ */
