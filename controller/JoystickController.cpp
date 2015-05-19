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
//      joystickEvent = event;
}

JoystickController::~JoystickController(void)
{
    SDL_JoystickClose(this->joystickOne);
    SDL_JoystickClose(this->joystickTwo);
}

//void JoystickController::update(MKCharacter *character, MKCharacter *character2) {
//    extern logger *Mylog;
//    char mensaje[100];
//    SDL_PollEvent(this->joystickEvent);
//
//    if (this->joystickEvent->type == SDL_JOYBUTTONDOWN || this->joystickEvent->type == SDL_JOYAXISMOTION) {
//        unsigned char pressedJoystick = this->joystickEvent->jbutton.which;
//        unsigned char pressedButton = this->joystickEvent->jbutton.button;
//        unsigned  char pressedAxis = this->joystickEvent->jaxis.axis;
//        int pressedValue = this->joystickEvent->jaxis.value;
//        cout << "Joystick number: " << (int) pressedJoystick << "Pressed button: " << (int) pressedButton << "Pressed axis: " << (int) pressedAxis << "Pressed value: "<< pressedValue << endl;
//        sprintf(mensaje, "JOYSTICK %d BUTTON PRESSED: %d", (int) pressedJoystick, (int) pressedButton);
//        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
//
//        // HACER SWTICH DE NUMERO DE JOYSTICK Y LUEGO DE CADA KEY PRESIONADA
//        switch (pressedJoystick) {
//            case 0:
//                if (pressedAxis == 0 && pressedValue > 1000) {
//                    Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
//                    character->setMovement("RIGHT");
//                    c1previousAxis = pressedAxis;
//                    c1previousKey = pressedValue;
//                    setCharacterSide(character, character2);
//                    timer = SDL_GetTicks();
//                }
//                if (pressedAxis == 0 && pressedValue < -1000) {
//                    Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
//                    character->setMovement("LEFT");
//                    c1previousAxis = pressedAxis;
//                    c1previousKey = pressedValue;
//                    setCharacterSide(character, character2);
//                    timer = SDL_GetTicks();
//                }
//                if (pressedAxis == 1 && pressedValue > 1000) {
//                    //if (c1previ) {
//                        Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
//                        character->setJump(true);
//                        setCharacterSide(character, character2);
//                    //}
//                    c1previousAxis = pressedAxis;
//                    c1previousKey = pressedValue;
//                }
//                if (pressedAxis == 1 && pressedValue < -1000) {
//                    Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
//                    character->setMovement("DUCK");
//                    c1previousAxis = pressedAxis;
//                    c1previousKey = pressedValue;
//                    timer = SDL_GetTicks();
//                }
//                if (pressedButton == c1kickDown) {
//                    if (c1previousAxis == 1 && c1previousValue < -1000) {
//                        Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
//                        character->setHit("KICKDOWN");
//                        c1previousKey = this->c1duck;
//                        character->setIsHiting(true);
//                        hitTimer = SDL_GetTicks();
//                    }
//                    else {
//                        Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
//                        character->setHit("KICK");
//                        c1previousKey = pressedButton;
//                        character->setIsHiting(true);
//                        hitTimer = SDL_GetTicks();
//                    }
//                }
//                if (pressedButton == c1punch) {
//                    if (c1previousAxis == 0 && c1previousValue < -1000) {
//                        character->setHit("PUNCHJUMPLEFT");
//                        character->setJump(true);
//                        Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la izquierda.", ERROR_LEVEL_INFO);
//                        character->setIsHiting(true);
//                        hitTimer = SDL_GetTicks();
//                    }
//                    else if (c1previousAxis == 0 && c1previousValue > 1000) {
//                        character->setHit("PUNCHJUMPRIGHT");
//                        character->setJump(true);
//                        Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la derecha.",
//                                   ERROR_LEVEL_INFO);
//                        character->setIsHiting(true);
//                        hitTimer = SDL_GetTicks();
//                    }
//                    if (c1previousAxis == 1 && c1previousValue < -1000) {
//                        character->setHit("PUNCHUP");
//                        Mylog->Log("movimiento del personaje: Golpe de puño ascendente.", ERROR_LEVEL_INFO);
//                        character->setIsHiting(true);
//                        hitTimer = SDL_GetTicks();
//                    }
//                    else {
//                        Mylog->Log("movimiento del personaje: Golpe de puño.", ERROR_LEVEL_INFO);
//                        character->setHit("PUNCH");
//                        c1previousKey = pressedButton;
//                        character->setIsHiting(true);
//                        hitTimer = SDL_GetTicks();
//                    }
//                }
//                if (pressedButton == c1shoot) {
//                    Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
//                    character->setHit("SHOOT");
//                    c1previousKey = pressedButton;
//                    character->setIsHiting(true);
//                    hitTimer = SDL_GetTicks();
//                }
//                if (pressedButton == c1block) {
//                    Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
//                    character->setHit("DEFENSE");
//                    c1previousKey = pressedButton;
//                    hitTimer = SDL_GetTicks();
//                }
//                c1previousKey = pressedButton;
//
//
//                break;
//            case 1:
//                if (pressedAxis == 0 && pressedValue > 1000) {
//                    Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
//                    character2->setMovement("RIGHT");
//                    c2previousKey = pressedButton;
//                    setCharacterSide(character, character2);
//                    timerChar2 = SDL_GetTicks();
//                }
//                if (pressedAxis == 0 && pressedValue < -1000) {
//                    Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
//                    character2->setMovement("LEFT");
//                    c2previousKey = pressedButton;
//                    setCharacterSide(character, character2);
//                    timerChar2 = SDL_GetTicks();
//                }
//                if (pressedAxis == 1 && pressedValue > 1000) {
//                 //   if (c2previousKey == this->c2jump) {
//                        Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
//                        character2->setJump(true);
//                        setCharacterSide(character, character2);
//                   // }
//                    c2previousKey = pressedButton;
//                }
//                if (pressedAxis == 1 && pressedValue < -1000) {
//                    Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
//                    character2->setMovement("DUCK");
//                    c2previousKey = pressedButton;;
//                    timerChar2 = SDL_GetTicks();
//                }
//
//                if (pressedButton == c2kickDown) {
//                    if (c2previousKey == this->c2duck) {
//                        Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
//                        character2->setHit("KICKDOWN");
//                        c2previousKey = this->c2duck;
//                        character2->setIsHiting(true);
//                        hitTimerChar2 = SDL_GetTicks();
//                    }
//                    else {
//                        Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
//                        character2->setHit("KICK");
//                        c2previousKey = pressedButton;
//                        character2->setIsHiting(true);
//                        hitTimerChar2 = SDL_GetTicks();
//                    }
//                }
//                if (pressedButton == c2punch) {
//                    if (c2previousAxis == 0 && c2previousValue < -1000) {
//                        character2->setHit("PUNCHJUMPLEFT");
//                        character2->setJump(true);
//                        Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la izquierda.",
//                                   ERROR_LEVEL_INFO);
//                        character2->setIsHiting(true);
//                        hitTimerChar2 = SDL_GetTicks();
//                    }
//                    else if (c2previousAxis == 0 && c2previousValue > 1000) {
//                        character2->setHit("PUNCHJUMPRIGHT");
//                        character2->setJump(true);
//                        Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la derecha.",
//                                   ERROR_LEVEL_INFO);
//                        character2->setIsHiting(true);
//                        hitTimerChar2 = SDL_GetTicks();
//                    }
//                    else if (c2previousAxis == 1 && c2previousValue < -1000) {
//                        character2->setHit("PUNCHUP");
//                        Mylog->Log("movimiento del personaje: Golpe de puño ascendente.", ERROR_LEVEL_INFO);
//                        character2->setIsHiting(true);
//                        hitTimerChar2 = SDL_GetTicks();
//                    }
//                    else {
//                        Mylog->Log("movimiento del personaje: Golpe de puño.", ERROR_LEVEL_INFO);
//                        character2->setHit("PUNCH");
//                        c2previousKey = pressedButton;
//                        character2->setIsHiting(true);
//                        hitTimerChar2 = SDL_GetTicks();
//                    }
//                }
//                if (pressedButton == c2shoot) {
//                    Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
//                    character2->setHit("SHOOT");
//                    c2previousKey = pressedButton;
//                    hitTimerChar2 = SDL_GetTicks();
//                }
//                if (pressedButton == c2block) {
//                    Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
//                    character2->setHit("DEFENSE");
//                    c2previousKey = pressedButton;
//                    hitTimerChar2 = SDL_GetTicks();
//                }
//
//                c2previousKey = pressedButton;
//        }
//
//    }/* else if (joystickEvent->type == SDL_JOYBUTTONUP) {
//            switch(joystickEvent->jbutton.button){
//                 case 0:
//                    c2previousKey = -1;
//                    break;
//                case 1:
//                    c2previousKey = -1;
//                    break;
//                case 2:
//                    c2previousKey = -1;
//                    break;
//                case 3:
//                    c2previousKey = -1;
//                    break;
//                default:
//                    testElapsedTime(character, character2);
//                    break;
//            }
//
//        } else {
//        testElapsedTime(character, character2);
//    }*/
//}

void JoystickController::update(MKCharacter *character, MKCharacter *character2, SDL_Event* mainEvent) {
    extern logger *Mylog;
    char mensaje[100];
    SDL_PollEvent(mainEvent);

    unsigned char pressedJoystick = mainEvent->jbutton.which;
    unsigned char pressedButton = mainEvent->jbutton.button;
    unsigned  char pressedAxis = mainEvent->jaxis.axis;
    int pressedValue = mainEvent->jaxis.value;

    if (mainEvent->type == SDL_JOYBUTTONDOWN || mainEvent->type == SDL_JOYAXISMOTION) {
        cout << "Joystick number: " << (int) pressedJoystick << "Pressed button: " << (int) pressedButton << "Pressed axis: " << (int) pressedAxis << "Pressed value: "<< pressedValue << " c1previousValue: " << c1previousValue<< endl;
        sprintf(mensaje, "JOYSTICK %d BUTTON PRESSED: %d", (int) pressedJoystick, (int) pressedButton);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);

        // HACER SWTICH DE NUMERO DE JOYSTICK Y LUEGO DE CADA KEY PRESIONADA
        switch (pressedJoystick) {
            case 0:
            	//Este if lo tengo q hacer para el joystick2 tambien
            	//Primero chequeo si es la misma tecla q en el ciclo anterior y comparo los valores para ver si es un KeyUp (para las flechas)

				//RIGHT
				if ((pressedAxis == c1previousAxis) && (pressedAxis == 0) && (pressedValue >= 0) && (c1previousValue > 0) && (c1previousValue - pressedValue >0))
				{
					cout << "KeyUp: Boton derecha"	<< endl;
				}
				else if ((pressedAxis == c1previousAxis) && (pressedAxis == 0) && (pressedValue <= 0) && (c1previousValue < 0) && (c1previousValue - pressedValue < 0))
				{
					cout << "KeyUp: Boton izquierda"	<< endl;
				}
				//Este no va pero lo dejo para el test
				else if ((pressedAxis == c1previousAxis) && (pressedAxis == 1) && (pressedValue >= 0) && (c1previousValue > 0) && (c1previousValue - pressedValue > 0))
				{
					cout << "KeyUp: Boton abajo"	<< endl;
				}
				else if ((pressedAxis == c1previousAxis) && (pressedAxis == 1) && (pressedValue <= 0) && (c1previousValue < 0) && (c1previousValue - pressedValue < 0))
				{
					cout << "KeyUp: Boton arriba"	<< endl;
				}
            	else
            	{
					if (pressedAxis == 0 && pressedValue > 1000) {
						//Guardo el valor anterior para simular el KeyUp
						c1previousAxis = pressedAxis;
						c1previousValue = pressedValue;
						cout << "KeyDown: Boton derecha"	<< endl;
						EventController::moveRight(character, character2);
					}
					if (pressedAxis == 0 && pressedValue < -1000) {
						//Guardo el valor anterior para simular el KeyUp
						c1previousAxis = pressedAxis;
						c1previousValue = pressedValue;
						cout << "KeyDown: Boton izquierda"	<< endl;
						EventController::moveLeft(character, character2);
					}
					if (pressedAxis == 1 && pressedValue > 1000) {
						//Guardo el valor anterior para simular el KeyUp
						c1previousAxis = pressedAxis;
						c1previousValue = pressedValue;
						cout << "KeyUp: Boton abajo"	<< endl;
						EventController::moveDown(character, character2);
					}
					if (pressedAxis == 1 && pressedValue < -1000) {
						cout << "KeyDown: Boton arriba"	<< endl;
						EventController::moveUp(character, character2);
					}
					if (pressedButton == c1kick) {
						EventController::highKick(character, character2);
					}

					if (pressedButton == c1kickDown) {
						EventController::lowKick(character, character2);
					}

					if (pressedButton == c1punch) {
						EventController::lowPunch(character, character2);
					}

					if (pressedButton == c1punchUp) {
						EventController::highPunch(character, character2);
					}

					if (pressedButton == c1shoot) {
						EventController::shoot(character, character2);
					}
					if (pressedButton == c1block) {
						//Guardo el valor anterior para simular el KeyUp
						c1previousAxis = pressedAxis;
						c1previousValue = pressedValue;
						EventController::block(character, character2);
					}
					c1previousKey = pressedButton;
            	}//else
                break;

  /*****************************************************************************************/
//            case 1:
//                if (pressedAxis == 0 && pressedValue > 1000) {
//                	//Guardo el valor anterior para simular el KeyUp
//                	c2previousAxis = pressedAxis;
//                	c2previousValue = pressedValue;
//                	EventController::moveRight(character2, character);
//                }
//                if (pressedAxis == 0 && pressedValue < -1000) {
//                	//Guardo el valor anterior para simular el KeyUp
//                	c2previousAxis = pressedAxis;
//                	c2previousValue = pressedValue;
//                	EventController::moveLeft(character2, character);
//                }
//                if (pressedAxis == 1 && pressedValue > 1000) {
//                	//Guardo el valor anterior para simular el KeyUp
//                	c2previousAxis = pressedAxis;
//                	c2previousValue = pressedValue;
//                	EventController::moveDown(character2, character);
//                }
//                if (pressedAxis == 1 && pressedValue < -1000) {
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
//					c2previousValue = pressedValue;
//                	EventController::block(character2, character);
//                }
////                c2previousKey = pressedButton;
//                break;
        } //switch
    }//If
    else if (mainEvent->type == SDL_JOYBUTTONUP) {
    	switch(pressedJoystick){
    	case 0:
			if (pressedButton == c1block){
				cout << "KeyUp: BlockRelease"	<< endl;
				EventController::blockRelease(character, character2);
			}
			break;
		case 1:
			if (pressedButton == c2block){
				cout << "KeyUp: BlockRelease2"	<< endl;
				EventController::blockRelease(character2, character);
			}

    	}
	}
}


void JoystickController::testElapsedTime(MKCharacter* character, MKCharacter* character2) {
//    if (timer + COMMANDDELAY < SDL_GetTicks()) {
//        character->setMovement("NONE");
//        timer = SDL_GetTicks();
//    }
//    if (hitTimer + COMMANDDELAYKIT < SDL_GetTicks()) {
//        character->setHit("NONE");
//        character->setIsHiting(false);
//        hitTimer = SDL_GetTicks();
//    }
//    if (timerChar2 + COMMANDDELAY < SDL_GetTicks()) {
//        character2->setMovement("NONE");
//        timerChar2 = SDL_GetTicks();
//    }
//    if (hitTimerChar2 + COMMANDDELAYKIT < SDL_GetTicks()) {
//        character2->setHit("NONE");
//        character2->setIsHiting(false);
//        hitTimerChar2 = SDL_GetTicks();
//    }
}
