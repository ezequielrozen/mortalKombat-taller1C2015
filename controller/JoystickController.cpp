//
// Created by mauri on 03/05/15.
//

#include "JoystickController.h"
#include "InputController.h"
#include "EventController.h"

JoystickController::JoystickController()
{
    joystickOne = NULL;
    joystickTwo = NULL;
    extern logger* Mylog;
    //cargando variables mapeo botones
    this->c1jump = Util::getInstance()->getMapaDeCaracteres(0);
    this->c1duck = Util::getInstance()->getMapaDeCaracteres(1);
    this->c1left = Util::getInstance()->getMapaDeCaracteres(2);
    this->c1right = Util::getInstance()->getMapaDeCaracteres(3);
    this->c1punch = Util::getInstance()->getMapaDeCaracteres(4);
    this->c1punchUp = Util::getInstance()->getMapaDeCaracteres(5);
    this->c1kick = Util::getInstance()->getMapaDeCaracteres(6);
    this->c1kickDown = Util::getInstance()->getMapaDeCaracteres(7);
    this->c1block = Util::getInstance()->getMapaDeCaracteres(8);
    this->c1shoot = Util::getInstance()->getMapaDeCaracteres(9);

    this->c2jump = Util::getInstance()->getMapaDeCaracteres(10);
    this->c2duck = Util::getInstance()->getMapaDeCaracteres(11);
    this->c2left = Util::getInstance()->getMapaDeCaracteres(12);
    this->c2right = Util::getInstance()->getMapaDeCaracteres(13);
    this->c2punch = Util::getInstance()->getMapaDeCaracteres(14);
    this->c2punchUp = Util::getInstance()->getMapaDeCaracteres(15);
    this->c2kick = Util::getInstance()->getMapaDeCaracteres(16);
    this->c2kickDown = Util::getInstance()->getMapaDeCaracteres(17);
    this->c2block = Util::getInstance()->getMapaDeCaracteres(18);
    this->c2shoot = Util::getInstance()->getMapaDeCaracteres(19);

    // Constructor

    char mensaje[100];
    sprintf(mensaje, "Joysticks conectados: %d", SDL_NumJoysticks());
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);

    switch (SDL_NumJoysticks()) {
        case 1:
            this->joystickOne = SDL_JoystickOpen(0);
            Mylog->Log(SDL_JoystickName(joystickOne), ERROR_LEVEL_INFO);
            cout << SDL_JoystickName(joystickOne) << endl;

            break;
        case 2:
            this->joystickOne = SDL_JoystickOpen(0);
            this->joystickTwo = SDL_JoystickOpen(1);
            Mylog->Log(SDL_JoystickName(joystickOne), ERROR_LEVEL_INFO);
            Mylog->Log(SDL_JoystickName(joystickTwo), ERROR_LEVEL_INFO);
            cout << SDL_JoystickName(joystickOne) << endl;
            cout << SDL_JoystickName(joystickTwo) << endl;

            break;
        default:
            Mylog->Log("No se detectaron los joysticks", ERROR_LEVEL_WARNING);
            break;
    }
    SDL_JoystickEventState(SDL_ENABLE);
    this->c1previousAxis = 0;
    this->c1previousAxisValue = 0;
    this->c2previousAxis = 0;
	this->c2previousAxisValue = 0;
	this->c1blockReleased = false;
	this->c2blockReleased = false;
	this->ducked = false;
	this->walkingLeft = false;
	this->walkingRight = false;
}

JoystickController::~JoystickController(void)
{
    SDL_JoystickClose(this->joystickOne);
    SDL_JoystickClose(this->joystickTwo);
}

void JoystickController::setDucked(bool value) {
	ducked = value;
}

void JoystickController::setWalkingLeft(bool value) {
	walkingLeft = value;
}

void JoystickController::setWalkingRight(bool value) {
	walkingRight = value;
}

void JoystickController::KeyUP_Right(unsigned char pressedAxis,
		int pressedAxisValue, bool printCout, MKCharacter* character,
		MKCharacter* character2) {
	c1previousAxis = pressedAxis;
	c1previousAxisValue = pressedAxisValue;
	printCout ? cout << "KeyUp: Boton derecha" << endl : "";
	setWalkingRight(false);
	EventController::moveRightRelease(character, character2);
}

void JoystickController::KeyUP_Down(unsigned char pressedAxis,
		int pressedAxisValue, bool printCout, MKCharacter* character,
		MKCharacter* character2) {
	c1previousAxis = pressedAxis;
	c1previousAxisValue = pressedAxisValue;
	printCout ? cout << "KeyUp: Boton abajo" << endl : "";
	setDucked(false);
	EventController::moveDownRelease(character, character2);
}

void JoystickController::KeyUP_Left(unsigned char pressedAxis,
		int pressedAxisValue, bool printCout, MKCharacter* character,
		MKCharacter* character2) {
	c1previousAxis = pressedAxis;
	c1previousAxisValue = pressedAxisValue;
	printCout ? cout << "KeyUp: Boton izquierda" << endl : "";
	setWalkingLeft(false);
	EventController::moveLeftRelease(character, character2);
}

void JoystickController::update(MKCharacter *character, MKCharacter *character2, SDL_Event* mainEvent) {
    extern logger *Mylog;
    char mensaje[100];
    SDL_PollEvent(mainEvent);

    unsigned char pressedJoystick = mainEvent->jbutton.which;
    unsigned char pressedButton = mainEvent->jbutton.button;
    unsigned  char pressedAxis = mainEvent->jaxis.axis;
    int pressedAxisValue = mainEvent->jaxis.value;

    bool printCout = false;

    if (mainEvent->type == SDL_JOYBUTTONDOWN || mainEvent->type == SDL_JOYAXISMOTION  || mainEvent->type == SDL_JOYBUTTONUP) {
        sprintf(mensaje, "JOYSTICK %d BUTTON PRESSED: %d", (int) pressedJoystick, (int) pressedButton);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    }else{	return;	}

    //KEYUP para los botones (no para las felchas)
    if (mainEvent->type == SDL_JOYBUTTONUP) {
    	switch(pressedJoystick){
    	case 0:
			if (pressedButton == c1block && !c1blockReleased){
				c1blockReleased = true;
				printCout ? cout << "KeyUp: BlockRelease"	<< endl : "";
				EventController::blockRelease(character, character2);
			}
			break;
		case 1:
			if (pressedButton == c2block && !c2blockReleased){
				c2blockReleased = true;
				printCout ? cout << "KeyUp: BlockRelease2"	<< endl : "";
				EventController::blockRelease(character2, character);
			}
    	}
	}

//    cout << "Joystick number: " << (int) pressedJoystick << " PressedButton: " << (int) pressedButton << " PressedAxis: " << (int) pressedAxis << " PressedAxisvalue: " << pressedAxisValue << " previousAxis: " <<  c1previousAxis << " previousAxisvalue: " << c1previousAxisValue << " type: " << mainEvent->type << endl;

	switch (pressedJoystick) {
		case 0:
			//Simulo los KEYUP de las flechas
			if ((mainEvent->type == SDL_JOYAXISMOTION)&&(pressedAxis == c1previousAxis)){
				if ((pressedAxis == 0) && (pressedAxisValue >= 0) && (c1previousAxisValue > 0) && (c1previousAxisValue - pressedAxisValue >0))
				{
					KeyUP_Right(pressedAxis, pressedAxisValue, printCout, character, character2);
				}
				if ((pressedAxis == 0) && (pressedAxisValue <= 0) && (c1previousAxisValue < 0) && (c1previousAxisValue - pressedAxisValue < 0))
				{
					KeyUP_Left(pressedAxis, pressedAxisValue, printCout, character,	character2);
				}
				if ((pressedAxis == 1) && (pressedAxisValue >= 0) && (c1previousAxisValue > 0) && (c1previousAxisValue - pressedAxisValue > 0))
				{
					KeyUP_Down(pressedAxis, pressedAxisValue, printCout, character,	character2);
				}
			}

			if (mainEvent->type == SDL_JOYAXISMOTION){
				if (pressedAxisValue == 0)
				{
					//Cuando hago DOWN, desp LEFT/RIGHT y suelto, no coinciden pressAxis con previoudAxis y no hace los KeyUp Left/Right y sigue caminando
					//por eso pregunto si estaba caminando y el AxisValue = 0, hago los keyUp.
					(walkingLeft) ?	KeyUP_Left(pressedAxis, pressedAxisValue, printCout, character,	character2) : setWalkingLeft(false);
					(walkingRight) ? KeyUP_Right(pressedAxis, pressedAxisValue, printCout, character, character2) : setWalkingRight(false);
				}
			}

			if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 0 && pressedAxisValue > 30080) {
				c1previousAxis = pressedAxis;
				c1previousAxisValue = pressedAxisValue;
				printCout ? cout << "KeyDown: Boton derecha"	<< endl : "";
				//Si estaba agachado hago el DownRelease
				ducked ? KeyUP_Down(pressedAxis, pressedAxisValue, printCout, character, character2) : setDucked(false);
				//Tengo q guardar esto porq si apreto RIGHT y muevo (analogico) a DOWN, no hace el KEYUP_RIGHT xq no coinciden pressedAxis con previousAxis
				setWalkingRight(true);
				EventController::moveRight(character, character2);
			}
			if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 0 && pressedAxisValue < -30080) {
				c1previousAxis = pressedAxis;
				c1previousAxisValue = pressedAxisValue;
				printCout ? cout << "KeyDown: Boton izquierda"	<< endl : "";
				//Si estaba agachado hago el DownRelease
				ducked ? KeyUP_Down(pressedAxis, pressedAxisValue, printCout, character, character2) : setDucked(false);
				setWalkingLeft(true);
				EventController::moveLeft(character, character2);
			}
			if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 1 && pressedAxisValue > 30080) {
				c1previousAxis = pressedAxis;
				c1previousAxisValue = pressedAxisValue;
				printCout ? cout << "KeyDown: Boton abajo"	<< endl : "";
				//Si esta caminando y apreto para abajo hago el released del Walk correspondiete.
				(walkingLeft) ?	KeyUP_Left(pressedAxis, pressedAxisValue, printCout, character,	character2) : setWalkingLeft(false);
				(walkingRight) ? KeyUP_Right(pressedAxis, pressedAxisValue, printCout, character, character2) : setWalkingRight(false);
				setDucked(true);
				EventController::moveDown(character, character2);
			}
			if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 1 && pressedAxisValue < -1000) {
				printCout ? cout << "KeyDown: Boton arriba"	<< endl: "";
				EventController::moveUp(character, character2);
			}
			if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c1kick) {
				printCout ? cout << "KeyDown: Boton c1kick"	<< endl : "";
				EventController::highKick(character, character2);
			}

			if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c1kickDown) {
				printCout ? cout << "KeyDown: Boton c1kickDown"	<< endl : "";
				EventController::lowKick(character, character2);
			}

			if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c1punch) {
				printCout ? cout << "KeyDown: Boton c1punch"	<< endl: "";
				EventController::lowPunch(character, character2);
			}

			if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c1punchUp) {
				printCout ? cout << "KeyDown: Boton c1punchUp"	<< endl: "";
				EventController::highPunch(character, character2);
			}

			if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c1shoot) {
				printCout ? cout << "KeyDown: Boton c1shoot"	<< endl : "";
				EventController::shoot(character, character2);
			}
			if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c1block) {
				c1blockReleased = false;
				printCout ? cout << "KeyDown: Boton c1block"	<< endl : "";
				EventController::block(character, character2);
			}
		break;

/*****************************************************************************************/
//            case 1:
//                if (pressedAxis == 0 && pressedAxisValue > 1000) {
//                	//Guardo el valor anterior para simular el KeyUp
//                	c2previousAxis = pressedAxis;
//                	c2previousValue = pressedAxisValue;
//                	EventController::moveRight(character2, character);
//                }
//                if (pressedAxis == 0 && pressedAxisValue < -1000) {
//                	//Guardo el valor anterior para simular el KeyUp
//                	c2previousAxis = pressedAxis;
//                	c2previousValue = pressedAxisValue;
//                	EventController::moveLeft(character2, character);
//                }
//                if (pressedAxis == 1 && pressedAxisValue > 1000) {
//                	//Guardo el valor anterior para simular el KeyUp
//                	c2previousAxis = pressedAxis;
//                	c2previousValue = pressedAxisValue;
//                	EventController::moveDown(character2, character);
//                }
//                if (pressedAxis == 1 && pressedAxisValue < -1000) {
//                	EventController::moveUp(character2, character);
//                }
//
//                if (pressedButton == c2kickDown) {
//                	EventController::lowKick(character2, character);
//                }
//                if (pressedButton == c2kick) {
//                	EventController::highKick(character2, character);
//                }
//
//                if (pressedButton == c2punch) {
//                	EventController::lowPunch(character2, character);
//                }
//                if (pressedButton == c2punchUp) {
//                	EventController::highPunch(character2, character);
//                }
//                if (pressedButton == c2shoot) {
//                	EventController::shoot(character2, character);
//                }
//                if (pressedButton == c2block) {
//                	//Guardo el valor anterior para simular el KeyUp
//					c2previousAxis = pressedAxis;
//					c2previousValue = pressedAxisValue;
//                	EventController::block(character2, character);
//                }
////                c2previousKey = pressedButton;
//                break;
	} //switch
}

