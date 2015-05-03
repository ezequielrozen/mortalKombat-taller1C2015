#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include "SDL2/SDL.h"
#include "../model/constantes.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include <bits/stl_list.h>
#include "../model/MKCharacter.h"
#include "../model/stage/Layer.h"

using namespace std;

class CameraController
{
public:
    CameraController();
    ~CameraController(void);

    bool update(MKCharacter* character, MKCharacter* character2, list<Layer*>* layer);

private:

	string cameraMovement;


};

#endif /* CAMERACONTROLLER_H_ */