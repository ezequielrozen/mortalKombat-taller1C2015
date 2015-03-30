#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include <string>
#include "MKSprite.h"
#include "GameSetup.h"
#include <math.h>
#include "SDL2/SDL.h"
#include "../controller/GameController.h"

using namespace std;

const int CHARACTER_WIDHT = 87;

class MKCharacter
{
public:
    MKCharacter(GameSetup* passed_SDL_Setup, int initialPosX, int initialPosY);
    ~MKCharacter(void);

    void Update(GameController* gameController);

    void moveRight();

    void moveLeft();

    int getWidth();

    int getX();

    int getY();

    string getMovement();

    //int getHeight();

private:

    GameSetup* gameSetup;

    string movement;

    int timeCheck;

    int posX;
    int posY;
};

#endif /* MKCHARACTER_H_ */
