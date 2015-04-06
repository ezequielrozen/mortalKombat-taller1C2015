#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include <string>
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"
#include "constantes.h"

using namespace std;

const int CHARACTER_WIDTH = 87;
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 500;

class MKCharacter
{
public:
    MKCharacter(int initialPosX, int initialPosY, float ancho, float alto, int z_index);
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

    string getJumpMovement();

    void setJumpMovement(string jumpMove);

    int getZ_index();

private:

    string movement;
    string jumpMovement;

    uint timeCheck;

    int posX;
    float posY;

    int z_index;
    float ancho;
    float alto;

    float velY;
    float accY;

    bool jumping;
};

#endif /* MKCHARACTER_H_ */
