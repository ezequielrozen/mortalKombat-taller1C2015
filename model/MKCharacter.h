#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include <string>
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"

using namespace std;

const int CHARACTER_WIDTH = 87;
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 500;

class MKCharacter
{
public:
    MKCharacter(int initialPosX, int initialPosY);
    ~MKCharacter(void);

    void moveRight();

    void moveLeft();

    void moveUp();

    void Update();

    int getWidth();

    int getX();

    int getY();

    string getMovement();

    void setMovement(string newMovement);

    void setJump(bool jump);

    bool isJumping();

private:

    string movement;

    uint timeCheck;

    int posX;
    float posY;

    float velY;
    float accY;

    bool jumping;
};

#endif /* MKCHARACTER_H_ */
