//
// Created by mauri on 03/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_JOYSTICKCONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_JOYSTICKCONTROLLER_H
#include <iostream>
#include "../model/MKCharacter.h"

using namespace std;

class JoystickController
{
public:
    JoystickController();
    ~JoystickController(void);

    void update(MKCharacter* character, MKCharacter* character2);

private:

};
#endif //MORTALKOMBAT_TALLER1C2015_JOYSTICKCONTROLLER_H
