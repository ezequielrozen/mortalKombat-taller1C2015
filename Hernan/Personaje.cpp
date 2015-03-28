/*
 * Personaje.cpp
 *
 *  Created on: 27/03/2015
 *      Author: her
 */

#include "Personaje.h"
#include "Utilidades.h"

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

Personaje::Personaje()
{
    //Initialize the offsets
    mPosX = (SCREEN_WIDTH - PERS_WIDTH) / 2;
    mPosY = ( SCREEN_HEIGHT - PERS_HEIGHT ) / 2;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Personaje::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= PERS_VEL; break;
            case SDLK_DOWN: mVelY += PERS_VEL; break;
            case SDLK_LEFT: mVelX -= PERS_VEL; break;
            case SDLK_RIGHT: mVelX += PERS_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += PERS_VEL; break;
            case SDLK_DOWN: mVelY -= PERS_VEL; break;
            case SDLK_LEFT: mVelX += PERS_VEL; break;
            case SDLK_RIGHT: mVelX -= PERS_VEL; break;
        }
    }
}

void Personaje::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PERS_WIDTH > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PERS_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}
