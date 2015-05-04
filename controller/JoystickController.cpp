//
// Created by mauri on 03/05/15.
//

#include "JoystickController.h"
#include "GameController.h"

JoystickController::JoystickController(SDL_Event* event)
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

    joystickEvent = event;
}

JoystickController::~JoystickController(void)
{
    SDL_JoystickClose(this->joystick);
}

void JoystickController::update(MKCharacter *character, MKCharacter *character2) {
    SDL_PollEvent(this->joystickEvent);

    if (this->joystickEvent->type == SDL_JOYBUTTONDOWN)
        cout << "JOYSTICK BUTTON PRESSED: " << (int) this->joystickEvent->jbutton.button << endl;
    // HACER SWTICH DE NUMERO DE JOYSTICK Y LUEGO DE CADA KEY PRESIONADA
}