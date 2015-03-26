/*
 * MKCharacter.h
 *
 *  Created on: Mar 24, 2015
 *      Author: gonza
 */

#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include "MKSprite.h"
#include "GameSetup.h"
#include <math.h>
#include "SDL2/SDL.h"

class MKCharacter
{
public:
        MKCharacter(GameSetup* passed_SDL_Setup);
        ~MKCharacter(void);

        void Update();
        void Draw();

        void moveRight();

        void moveLeft();

private:

        GameSetup* gameSetup;

        MKSprite* scorpion;
        int timeCheck;

        bool stopAnimation;
};

#endif /* MKCHARACTER_H_ */
