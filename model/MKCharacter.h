#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include <string>
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"
#include "constantes.h"

using namespace std;

class MKCharacter
{
public:
    MKCharacter(float initialPosX, float initialPosY, float ancho, float alto, int z_index);
    ~MKCharacter(void);

    void moveRight();

    void moveLeft();

    void moveUp();

    void Update();

    void UpdateJump();

    float getWidth();

    float getHeight();

    double getX();

    double getY();

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

    //uint timeCheck;

    double posX;
    double posY;

    int z_index;
    float ancho;
    float alto;

    double velY;
    double accY;

    bool jumping;

    double step;
};

#endif /* MKCHARACTER_H_ */
