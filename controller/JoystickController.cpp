//
// Created by mauri on 03/05/15.
//

#include "JoystickController.h"

JoystickController::JoystickController()
{
    // Constructor
    SDL_Init(SDL_INIT_JOYSTICK);
}


JoystickController::~JoystickController(void)
{
    // Desctructor
}