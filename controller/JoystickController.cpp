//
// Created by mauri on 03/05/15.
//

#include "JoystickController.h"

JoystickController::JoystickController()
{
    // Constructor
    SDL_Init(SDL_INIT_JOYSTICK);

    cout << "Joysticks conectados: " << SDL_NumJoysticks() << endl;

    if (SDL_NumJoysticks() < 1)
        cout << "NO JOYSTICKS DETECTED" << endl;
        // Loggear que no se detectaron joysticks
    else {
        this->joystick = SDL_JoystickOpen(0);
        cout << SDL_JoystickName(joystick) << endl;
    }

    joystickEvent = new SDL_Event();
}

JoystickController::~JoystickController(void)
{
    delete this->joystickEvent;
    // Desctructor
}

void JoystickController::update(MKCharacter *character, MKCharacter *character2) {
    SDL_PollEvent(this->joystickEvent);
    while ( SDL_PollEvent(this->joystickEvent) != 0 ) {

       // if (this->joystickEvent->type == AXIS)
            cout << "JOYSTICK BUTTON PRESSED" << endl;
    }
}