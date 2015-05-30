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
};

#endif /* FATALITYHITTING_H_ */
