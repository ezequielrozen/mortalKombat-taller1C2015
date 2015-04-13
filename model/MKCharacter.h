#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include <string>
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"
#include "constantes.h"
#include "logger.h"

using namespace std;

class MKCharacter
{
public:
    MKCharacter(float initialPosX, float initialPosY, float ancho, float alto, int z_index,
                        char* walkFile, char* stanceFile, char* jumpFile, char* sideJumpFile);
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

    char* getWalk();
    char* getStance();
    char* getJump();
    char* getSideJump();


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

    double stageFloor;

    bool jumping;

    double step;

    char* walk;
    char* stance;
    char* jump;
    char* sideJump;
};

#endif /* MKCHARACTER_H_ */
