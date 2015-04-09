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
    CameraController(int pScreenWidth);
    ~CameraController(void);

    void update(MKCharacter* character, list<Layer*>* layer);

private:

	string cameraMovement;

	int ScreenWidth;

};

#endif /* CAMERACONTROLLER_H_ */