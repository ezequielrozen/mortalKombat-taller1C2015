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
    MKCharacter(float initialPosX, float ancho, float alto, int z_index, int pCharacterNumber, string name);
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

    string getHit();

    void setHit(string newHit);

    void setJump(bool jump);

    bool isJumping();

    string getJumpMovement();

    void setJumpMovement(string jumpMove);

    int getZ_index();

    char* getFileMovement(const char* moveName);

    void receiveBlow(int force);

    int getLife();

    void setLife(int life);

    bool isAlive();

    void setName(string aName);

    string getName();

    void setStageFloor(double);

    void setPosY(double);

    void setHitWidth(float width);

    float getHitWidth();

    void setHitDelay(int delay);

    int getHitDelay();

    bool getIsHiting();

    void setIsHiting(bool);

    char getCharacterSide();

    void setCharacterSide(char);


private:
    void RestartJump();
    string movement;
    string jumpMovement;
    string hitMovement;

    double auxPosX;
    double posX;
    double posY;
    bool isHiting;

    int z_index;
    float ancho;
    float alto;

    float hitWidth;
    int hitDelay;

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
	char characterSide;

    string name;
};

#endif /* MKCHARACTER_H_ */
