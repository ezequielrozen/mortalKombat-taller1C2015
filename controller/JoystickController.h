//
// Created by mauri on 03/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_JOYSTICKCONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_JOYSTICKCONTROLLER_H
#include <iostream>
#include "../model/MKCharacter.h"
#include "../model/util/Util.h"

using namespace std;

class JoystickController
{
public:
    JoystickController();
    ~JoystickController(void);

    void update(MKCharacter* character, MKCharacter* character2, SDL_Event* joystickEvent);
    SDL_Event* getEvent();
private:
    SDL_Joystick* joystickOne;
    SDL_Joystick* joystickTwo;

    int timer;
    int timerChar2;
    int hitTimer;
    int hitTimerChar2;

        //botones
    unsigned char c1jump;
    unsigned char c1duck;
    unsigned char c1left;
    unsigned char c1right;
    unsigned char c1punch;
    unsigned char c1punchUp;
    unsigned char c1kick;
    unsigned char c1kickDown;
    unsigned char c1block;
    unsigned char c1shoot;
    unsigned char c2jump;
    unsigned char c2duck;
    unsigned char c2left;
    unsigned char c2right;
    unsigned char c2punch;
    unsigned char c2punchUp;
    unsigned char c2kick;
    unsigned char c2kickDown;
    unsigned char c2block;
    unsigned char c2shoot;

    int c1previousAxis;
    int c1previousAxisValue;
    int c2previousAxis;
    int c2previousAxisValue;

	bool c1blockReleased;
	bool c2blockReleased;
	bool ducked;
	bool walkingLeft;
	bool walkingRight;

	bool EjeXPositivo(unsigned char pressedAxis, int pressedAxisValue, SDL_Event* mainEvent);
	bool EjeXNegativo(unsigned char pressedAxis, int pressedAxisValue, SDL_Event* mainEvent);
	bool EjeYPositivo(unsigned char pressedAxis, int pressedAxisValue, SDL_Event* mainEvent);
	bool EjeYNegativo(unsigned char pressedAxis, int pressedAxisValue, SDL_Event* mainEvent);
	void setDucked(bool value);
	void setWalkingLeft(bool value);
	void setWalkingRight(bool value);
	void KeyUP_Right(unsigned char pressedAxis, int pressedAxisValue,
			bool printCout, MKCharacter* character, MKCharacter* character2);
	void KeyUP_Down(unsigned char pressedAxis, int pressedAxisValue,
			bool printCout, MKCharacter* character, MKCharacter* character2);
	void KeyUP_Left(unsigned char pressedAxis, int pressedAxisValue,
			bool printCout, MKCharacter* character, MKCharacter* character2);
};
#endif //MORTALKOMBAT_TALLER1C2015_JOYSTICKCONTROLLER_H
