/*
 * Throwable.h
 *
 *  Created on: 30/05/2015
 *      Author: her
 */

#ifndef THROWABLE_H_
#define THROWABLE_H_

using namespace std;

class Throwable {
public:

	virtual void update();
	virtual bool isActive();
	virtual void destroy();
	virtual float getPositionX();
	virtual float getPositionY();
	virtual void throwWeapon(float initialPositionX, float initialPositionY, char direction);
	virtual float getWidth();
	virtual float getHeight();
	virtual bool isImpact();
	virtual bool isStarting();
    virtual void setImpactingWeaponIce(bool);
    virtual bool getImpactingWeaponIce();
	virtual int getCurrentWeaponIce();
};

#endif /* THROWABLE_H_ */
