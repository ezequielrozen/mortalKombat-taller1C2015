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
    MKCharacter(float initialPosX, float initialPosY, float ancho, float alto, int z_index, int pCharacterNumber);
    ~MKCharacter(void);

    void moveRight();

    void moveLeft();

    void moveUp();

    void move();

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

    char* getFileMovement(const char* moveName);

    void receiveBlow(int force);

    int getLife();

    bool isAlive();


private:
    void RestartJump();
    string movement;
    string jumpMovement;

    double posX;
    double posY;

    int z_index;
    float ancho;
    float alto;

    double velY;
    double accY;
    double jumpTime;
    double yMax;
    double actualVel;
    float proporcionVel;
    double stageFloor;

    bool jumping;

    double step;

    //uso esta variable para controlar que no se vaya de la pantalla por arriba cuando ponen valores raros: "alto-px": 300; "alto": 300; y-piso: 50
	float limiteSuperior;

	int life;
	int characterNumber;

};

#endif /* MKCHARACTER_H_ */
