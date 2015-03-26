/*
 * MKMain.h
 *
 *  Created on: Mar 24, 2015
 *      Author: gonza
 */

#ifndef MKMAIN_H_
#define MKMAIN_H_

#include "GameSetup.h"
#include "MKSprite.h"
#include "MKCharacter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <math.h>

class MKMain
{
public:
        MKMain(int passed_ScreenWidth, int passed_ScreenHeight);
        ~MKMain(void);
        void GameLoop();

private:

        MKCharacter *scorpion;

        int ScreenWidth;
        int ScreenHeight;

        bool quit;

        GameSetup* gameSetup;

};

#endif /* MKMAIN_H_ */
