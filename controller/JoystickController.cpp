//
// Created by mauri on 03/05/15.
//

#include "JoystickController.h"
#include "GameController.h"

JoystickController::JoystickController(SDL_Event* event)
{
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
    SDL_Init(SDL_INIT_JOYSTICK);
    char mensaje[100];
    sprintf(mensaje, "Joysticks conectados: %d", SDL_NumJoysticks());
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);

    if (SDL_NumJoysticks() < 1)
        Mylog->Log("No se detectaron los joysticks", ERROR_LEVEL_WARNING);
        // Loggear que no se detectaron joysticks
    else {
        this->joystick = SDL_JoystickOpen(0);
        Mylog->Log(SDL_JoystickName(joystick), ERROR_LEVEL_INFO);
//        cout << SDL_JoystickName(joystick) << endl;
    }

    joystickEvent = event;
}

JoystickController::~JoystickController(void)
{
    SDL_JoystickClose(this->joystick);
}

void JoystickController::update(MKCharacter *character, MKCharacter *character2) {
    extern logger* Mylog;
    char mensaje[100];
    SDL_PollEvent(this->joystickEvent);

    if (this->joystickEvent->type == SDL_JOYBUTTONDOWN){
        unsigned char pressedJoystick = this->joystickEvent->jbutton.which;
        unsigned char pressedButton = this->joystickEvent->jbutton.button;
        sprintf(mensaje, "JOYSTICK %d BUTTON PRESSED: %d", (int) pressedJoystick, (int) pressedButton);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);

        // HACER SWTICH DE NUMERO DE JOYSTICK Y LUEGO DE CADA KEY PRESIONADA
        switch (pressedJoystick){
            case 0:
                if(pressedButton == c1right){
                                Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
                                character->setMovement("RIGHT");
                                c1previousKey = pressedButton;
                                setCharacterSide(character, character2);
                                timer = SDL_GetTicks();

                }
                    if(pressedButton == c1left){
                                Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
                                character->setMovement("LEFT");
                                c1previousKey = pressedButton;
                                setCharacterSide(character, character2);
                                timer = SDL_GetTicks();
                }
                    if(pressedButton == c1jump){
                                if (c1previousKey == SDLK_UP){
                                    Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
                                    character->setJump(true);
                                    setCharacterSide(character, character2);
                                }
                                c1previousKey = pressedButton;
                    }
                    if(pressedButton == c1duck){
                                Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
                                character->setMovement("DUCK");
                                c1previousKey = pressedButton;
                                timer = SDL_GetTicks();
                    }
                    if(pressedButton == c1kickDown){
                                if (c1previousKey == this->c1duck){
                                    Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
                                    character->setHit("KICKDOWN");
                                    c1previousKey = this->c1duck;
                                    character->setIsHiting(true);
                                    hitTimer = SDL_GetTicks();
                                }
                                else{
                                    Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
                                    character->setHit("KICK");
                                    c1previousKey = pressedButton;
                                    character->setIsHiting(true);
                                    hitTimer = SDL_GetTicks();
                                }
                        }
                    if(pressedButton == c1punch){
                                if (c1previousKey == this->c1left){
                                    character->setHit("PUNCHJUMPLEFT");
                                    character->setJump(true);
                                    Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la izquierda.", ERROR_LEVEL_INFO);
                                    character->setIsHiting(true);
                                    hitTimer = SDL_GetTicks();
                                }
                                else if (c1previousKey == this->c1right){
                                    character->setHit("PUNCHJUMPRIGHT");
                                    character->setJump(true);
                                    Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la derecha.", ERROR_LEVEL_INFO);
                                    character->setIsHiting(true);
                                    hitTimer = SDL_GetTicks();
                                }
                                else if (c1previousKey == this->c1duck){
                                    character->setHit("PUNCHUP");
                                    Mylog->Log("movimiento del personaje: Golpe de puño ascendente.", ERROR_LEVEL_INFO);
                                    character->setIsHiting(true);
                                    hitTimer = SDL_GetTicks();
                                }
                                else{
                                    Mylog->Log("movimiento del personaje: Golpe de puño.", ERROR_LEVEL_INFO);
                                    character->setHit("PUNCH");
                                    c1previousKey = pressedButton;
                                    character->setIsHiting(true);
                                    hitTimer = SDL_GetTicks();
                                }
                        }
                    if(pressedButton == c1shoot){
                                Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
                                character->setHit("SHOOT");
                                c1previousKey = pressedButton;
                                character->setIsHiting(true);
                                hitTimer = SDL_GetTicks();
                    }
                    if(pressedButton == c1block){
                                Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
                                character->setHit("DEFENSE");
                                c1previousKey = pressedButton;
                                hitTimer = SDL_GetTicks();
                    }
                    c1previousKey = pressedButton;


                break;
            case 1:
                    if(pressedButton == c2right){
							Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
							character2->setMovement("RIGHT");
							c2previousKey = pressedButton;
							setCharacterSide(character, character2);
							timerChar2 = SDL_GetTicks();
                }
				if(pressedButton == c2left){
							Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
							character2->setMovement("LEFT");
							c2previousKey = pressedButton;
							setCharacterSide(character, character2);
							timerChar2 = SDL_GetTicks();
                }
				if(pressedButton == c2jump){
							if (c2previousKey == this->c2jump)	{
								Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
								character2->setJump(true);
								setCharacterSide(character, character2);
							}
							c2previousKey = pressedButton;
                }
				if(pressedButton == c2duck){
							Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
							character2->setMovement("DUCK");
							c2previousKey = pressedButton;;
							timerChar2 = SDL_GetTicks();
                }

				if(pressedButton == c2kickDown){
							if (c2previousKey == this->c2duck){
								Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
								character2->setHit("KICKDOWN");
								c2previousKey = this->c2duck;
								character2->setIsHiting(true);
								hitTimerChar2 = SDL_GetTicks();
							}
							else{
								Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
								character2->setHit("KICK");
								c2previousKey = pressedButton;
								character2->setIsHiting(true);
								hitTimerChar2 = SDL_GetTicks();
							}
                }
				if(pressedButton == c2punch){
							if (c2previousKey == this->c2left){
								character2->setHit("PUNCHJUMPLEFT");
								character2->setJump(true);
								Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la izquierda.", ERROR_LEVEL_INFO);
								character2->setIsHiting(true);
								hitTimerChar2 = SDL_GetTicks();
							}
							else if (c2previousKey == this->c2right){
								character2->setHit("PUNCHJUMPRIGHT");
								character2->setJump(true);
								Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la derecha.", ERROR_LEVEL_INFO);
								character2->setIsHiting(true);
								hitTimerChar2 = SDL_GetTicks();
							}
							else if (c2previousKey == this->c2duck){
								character2->setHit("PUNCHUP");
								Mylog->Log("movimiento del personaje: Golpe de puño ascendente.", ERROR_LEVEL_INFO);
								character2->setIsHiting(true);
								hitTimerChar2 = SDL_GetTicks();
							}
							else{
								Mylog->Log("movimiento del personaje: Golpe de puño.", ERROR_LEVEL_INFO);
								character2->setHit("PUNCH");
								c2previousKey = pressedButton;
								character2->setIsHiting(true);
								hitTimerChar2 = SDL_GetTicks();
							}
                    }
                    if(pressedButton == c2shoot){
                                Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
                                character2->setHit("SHOOT");
                                c2previousKey = pressedButton;
                                hitTimerChar2 = SDL_GetTicks();
                    }
                    if(pressedButton == c2block){
                                Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
                                character2->setHit("DEFENSE");
                                c2previousKey = pressedButton;
                                hitTimerChar2 = SDL_GetTicks();
                    }

                        c2previousKey = pressedButton;


        }

    }
}
