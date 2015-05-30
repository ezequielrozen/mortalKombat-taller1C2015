//
// Created by mauri on 03/05/15.
//

#include "JoystickController.h"
#include "InputController.h"
#include "EventController.h"

JoystickController::JoystickController(char number)
{
    extern logger* Mylog;
    joystickNumber = number;

    //cargando variables mapeo botones
    if (number == 0)
    {
		this->c0jump = Util::getInstance()->getMapaDeCaracteres(0);
		this->c0duck = Util::getInstance()->getMapaDeCaracteres(1);
		this->c0left = Util::getInstance()->getMapaDeCaracteres(2);
		this->c0right = Util::getInstance()->getMapaDeCaracteres(3);
		this->c0LowPunch = Util::getInstance()->getMapaDeCaracteres(4);
		this->c0HighPunch = Util::getInstance()->getMapaDeCaracteres(5);
		this->c0HighKick = Util::getInstance()->getMapaDeCaracteres(6);
		this->c0LowKick = Util::getInstance()->getMapaDeCaracteres(7);
		cout << (int)this->c0LowKick << endl;
		this->c0block = Util::getInstance()->getMapaDeCaracteres(8);
		this->c0shoot = Util::getInstance()->getMapaDeCaracteres(9);
		this->c0duckPunch = Util::getInstance()->getMapaDeCaracteres(20);
    }
    else
    {
    	this->c0jump = Util::getInstance()->getMapaDeCaracteres(10);
		this->c0duck = Util::getInstance()->getMapaDeCaracteres(11);
		this->c0left = Util::getInstance()->getMapaDeCaracteres(12);
		this->c0right = Util::getInstance()->getMapaDeCaracteres(13);
		this->c0LowPunch = Util::getInstance()->getMapaDeCaracteres(14);
		this->c0HighPunch = Util::getInstance()->getMapaDeCaracteres(15);
		this->c0HighKick = Util::getInstance()->getMapaDeCaracteres(16);
		this->c0LowKick = Util::getInstance()->getMapaDeCaracteres(17);
		cout << (int)this->c0LowKick << "-----------------" << endl;
		this->c0block = Util::getInstance()->getMapaDeCaracteres(18);
		this->c0shoot = Util::getInstance()->getMapaDeCaracteres(19);
		this->c0duckPunch = Util::getInstance()->getMapaDeCaracteres(21);

    }

    this->c0previousAxis = 0;
    this->c0previousAxisValue = 0;
	this->c0blockReleased = false;
	this->c0shootReleased = true; //la uso para saber si ya hizo keyUp de la tecla shoot xq por cada keyDown dispara n veces y mata al oponente sino.
	this->c0ducked = false;
	this->c0walkingLeft = false;
	this->c0walkingRight = false;

	this->eventController = new EventController();
}

JoystickController::~JoystickController(void) {
	delete this->eventController;
}

void JoystickController::setDucked(bool value) {
	c0ducked = value;
}

void JoystickController::setWalkingLeft(bool value) {
	c0walkingLeft = value;
}

void JoystickController::setWalkingRight(bool value) {
	c0walkingRight = value;
}

void JoystickController::KeyUP_Right(unsigned char pressedAxis,	int pressedAxisValue, bool printCout, MKCharacter* character,
									MKCharacter* character2) {

	c0previousAxis = pressedAxis;
	c0previousAxisValue = pressedAxisValue;
	printCout ? cout << "KeyUp: Boton derecha" << endl : "";
	setWalkingRight(false);
	this->eventController->moveRightRelease(character, character2);
}

void JoystickController::KeyUP_Down(unsigned char pressedAxis, int pressedAxisValue, bool printCout, MKCharacter* character,
									MKCharacter* character2) {
	c0previousAxis = pressedAxis;
	c0previousAxisValue = pressedAxisValue;
	printCout ? cout << "KeyUp: Boton abajo" << endl : "";
	setDucked(false);
	this->eventController->moveDownRelease(character, character2);
}

void JoystickController::KeyUP_Left(unsigned char pressedAxis, int pressedAxisValue, bool printCout, MKCharacter* character,
									MKCharacter* character2) {
	c0previousAxis = pressedAxis;
	c0previousAxisValue = pressedAxisValue;
	printCout ? cout << "KeyUp: Boton izquierda" << endl : "";
	setWalkingLeft(false);
	this->eventController->moveLeftRelease(character, character2);
}

void JoystickController::update(MKCharacter *character, MKCharacter *character2, SDL_Event* mainEvent) {
    extern logger *Mylog;
    char mensaje[100];
//    SDL_PollEvent(mainEvent);

    unsigned char pressedButton = mainEvent->jbutton.button;
    unsigned  char pressedAxis = mainEvent->jaxis.axis;
    int pressedAxisValue = mainEvent->jaxis.value;

    bool printCout = false;

    if (mainEvent->type == SDL_JOYBUTTONDOWN || mainEvent->type == SDL_JOYAXISMOTION  || mainEvent->type == SDL_JOYBUTTONUP) {
        sprintf(mensaje, "JOYSTICK %d BUTTON PRESSED: %d", (int) pressedButton);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    }else{	return;	}

    //KEYUP para los botones (no para las felchas)
    if (mainEvent->type == SDL_JOYBUTTONUP) {
		if (pressedButton == c0block && !c0blockReleased){
			c0blockReleased = true;
			printCout ? cout << "KeyUp: BlockRelease"	<< endl : "";
			this->eventController->blockRelease(character, character2);
		}
		if (pressedButton == c0shoot){
			this->c0shootReleased = true;
		}
	}

//    cout << "Joystick number: " << (int) this->joystickNumber << " PressedButton: " << (int) pressedButton << " PressedAxis: " << (int) pressedAxis << " PressedAxisvalue: " << pressedAxisValue << " previousAxis: " <<  c0previousAxis << " previousAxisvalue: " << c0previousAxisValue << " type: " << mainEvent->type << endl;


	//Simulo los KEYUP de las flechas
	if ((mainEvent->type == SDL_JOYAXISMOTION)&&(pressedAxis == c0previousAxis)){
		if ((pressedAxis == 0) && (pressedAxisValue >= 0) && (c0previousAxisValue > 0) && (c0previousAxisValue - pressedAxisValue >0))
		{
			KeyUP_Right(pressedAxis, pressedAxisValue, printCout, character, character2);
		}
		if ((pressedAxis == 0) && (pressedAxisValue <= 0) && (c0previousAxisValue < 0) && (c0previousAxisValue - pressedAxisValue < 0))
		{
			KeyUP_Left(pressedAxis, pressedAxisValue, printCout, character,	character2);
		}
		if ((pressedAxis == 1) && (pressedAxisValue >= 0) && (c0previousAxisValue > 0) && (c0previousAxisValue - pressedAxisValue > 0))
		{
			KeyUP_Down(pressedAxis, pressedAxisValue, printCout, character,	character2);
		}
	}

	if (mainEvent->type == SDL_JOYAXISMOTION){
		if (pressedAxisValue == 0)
		{
			//Cuando hago DOWN, desp LEFT/RIGHT y suelto, no coinciden pressAxis con previoudAxis y no hace los KeyUp Left/Right y sigue caminando
			//por eso pregunto si estaba caminando y el AxisValue = 0, hago los keyUp.
			(c0walkingLeft) ?	KeyUP_Left(pressedAxis, pressedAxisValue, printCout, character,	character2) : setWalkingLeft(false);
			(c0walkingRight) ? KeyUP_Right(pressedAxis, pressedAxisValue, printCout, character, character2) : setWalkingRight(false);
		}
	}

	if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 0 && pressedAxisValue > 30080) {
		c0previousAxis = pressedAxis;
		c0previousAxisValue = pressedAxisValue;
		printCout ? cout << "KeyDown: Boton derecha"	<< endl : "";
		//Si estaba agachado hago el DownRelease
		c0ducked ? KeyUP_Down(pressedAxis, pressedAxisValue, printCout, character, character2) : setDucked(false);
		//Tengo q guardar esto porq si apreto RIGHT y muevo (analogico) a DOWN, no hace el KEYUP_RIGHT xq no coinciden pressedAxis con previousAxis
		setWalkingRight(true);
		this->eventController->moveRight(character, character2);
	}
	if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 0 && pressedAxisValue < -30080) {
		c0previousAxis = pressedAxis;
		c0previousAxisValue = pressedAxisValue;
		printCout ? cout << "KeyDown: Boton izquierda"	<< endl : "";
		//Si estaba agachado hago el DownRelease
		c0ducked ? KeyUP_Down(pressedAxis, pressedAxisValue, printCout, character, character2) : setDucked(false);
		setWalkingLeft(true);
		this->eventController->moveLeft(character, character2);
	}
	if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 1 && pressedAxisValue > 30080) {
		c0previousAxis = pressedAxis;
		c0previousAxisValue = pressedAxisValue;
		printCout ? cout << "KeyDown: Boton abajo"	<< endl : "";
		//Si esta caminando y apreto para abajo hago el released del Walk correspondiete.
		(c0walkingLeft) ?	KeyUP_Left(pressedAxis, pressedAxisValue, printCout, character,	character2) : setWalkingLeft(false);
		(c0walkingRight) ? KeyUP_Right(pressedAxis, pressedAxisValue, printCout, character, character2) : setWalkingRight(false);
		setDucked(true);
		this->eventController->moveDown(character, character2);
	}
	if (mainEvent->type == SDL_JOYAXISMOTION && pressedAxis == 1 && pressedAxisValue < -1000) {
		printCout ? cout << "KeyDown: Boton arriba"	<< endl: "";
		this->eventController->moveUp(character, character2);
	}
	if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c0HighKick) {
		printCout ? cout << "KeyDown: Boton c0HighKick"	<< endl : "";
		this->eventController->highKick(character, character2);
	}

	if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c0LowKick) {
		printCout ? cout << "KeyDown: Boton c0LowKick"	<< endl : "";
		this->eventController->lowKick(character, character2);
	}

	if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c0duckPunch) {
		printCout ? cout << "KeyDown: Boton c0duckPunch"	<< endl: "";
		this->eventController->duckPunch(character, character2);
	}

	if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c0HighPunch) {
			printCout ? cout << "KeyDown: Boton c0HighPunch"	<< endl: "";
			this->eventController->highPunch(character, character2);
	}

	if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c0LowPunch) {
			printCout ? cout << "KeyDown: Boton c0LowPunch"	<< endl: "";
			this->eventController->lowPunch(character, character2);
	}

	if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c0shoot && (this->c0shootReleased)) {
		this->c0shootReleased = false;
		printCout ? cout << "KeyDown: Boton c0shoot"	<< endl : "";
		this->eventController->shoot(character, character2);
	}
	if (mainEvent->type == SDL_JOYBUTTONDOWN && pressedButton == c0block) {
		c0blockReleased = false;
		printCout ? cout << "KeyDown: Boton c0block"	<< endl : "";
		this->eventController->block(character, character2);
	}

}

