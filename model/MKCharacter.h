#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include <string>
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"
#include "../controller/GameController.h"

using namespace std;

const int CHARACTER_WIDTH = 87;
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 500;

class MKCharacter
{
public:
    MKCharacter(int initialPosX, int initialPosY);
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

    string movement;

    int timeCheck;

    int posX;
    int posY;
};

#endif /* MKCHARACTER_H_ */
