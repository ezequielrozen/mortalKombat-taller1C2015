#ifndef MKCHARACTER_H_
#define MKCHARACTER_H_

#include <string>
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"
#include "constantes.h"
#include "logger.h"
#include "character/CharacterState.h"
#include "Throwable.h"
#include "Weapon.h"
#include "Fire.h"

using namespace std;

class CharacterState;

class MKCharacter
{
public:
    MKCharacter(float initialPosX, float ancho, float alto, int z_index, int pCharacterNumber, string name);
    ~MKCharacter(void);

    // State
    void setState(CharacterState* state);
    void update(Events aEvent);

    bool isMovingLeft();
    bool isMovingRight();
    bool isHitting();
    bool isDucking();
    bool isBlocking();
    bool isJumping();
    bool isReceivingHit();
    bool isBeingOverPassedRight();
    bool isBeingOverPassedLeft();

    double getYMax();
    double getVelY();
    double getAccY();

    void moveRight();
    void moveLeft();
    void moveUp();
    void move();

    void characterUpdate();

    float getWidth();
    float getHeight();

    double getX();

    double getStagePosX();

    void increaseStagePosX();

    void decreaseStagePosX();

    void setInitialPosition(double);

    double getY();

    int getZ_index();

    char* getFileMovement(const char* moveName);

    void receiveBlow(int force, char direction);

    int getLife();

    void setLife(int life);

    bool isAlive();

    void setName(string aName);

    string getName();

    void setStageFloor(double);

    void setPosY(double);

    char getCharacterSide();

    void setCharacterSide(char);

    bool isAscending();

    string getState();

    float getStateWidth();

    bool impacts();

    Throwable* getWeapon();

    void throwWeapon();

    Throwable* getWeaponFire();

    void throwWeaponFire();

    float getStateHeight();

    void disableImpact();

    void moveForced(double x);

    void moveRightFaster();

    void moveLeftFaster();

    void setStopX(float x);

private:

    // State
    CharacterState* state;
    double auxPosX;
    double posX;
    double posY;
    double stagePosX;

    int z_index;
    float ancho;
    float alto;

    double jumpTime;
    double stageFloor;
    bool ascending;

    double step;

	int life;
	int characterNumber;
	char characterSide;

    string name;

    float stopX;
    void updateOverPassing();
    // Weapon
    Throwable* weapon;
    Throwable* weaponFire;
    bool weaponFireUsed;
};

#endif /* MKCHARACTER_H_ */
