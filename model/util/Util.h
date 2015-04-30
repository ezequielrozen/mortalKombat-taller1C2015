#ifndef MORTALKOMBAT_TALLER1C2015_UTIL_H
#define MORTALKOMBAT_TALLER1C2015_UTIL_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <list>
#include "../constantes.h"

using namespace std;

class Util {

public:

    static Util* getInstance();
    Util();
    ~Util();
    int getWindowWidth();
    void setWindowWidth(int);
    int getWindowHeight();
    void setWindowHeight(int);
    float getLogicalWindowWidth();
    void setLogicalWindowWidth(float);
    float getLogicalStageWidth();
    void setLogicalStageWidth(float);
    float getLogicalWindowHeight();
    void setLogicalWindowHeight(float);
    float getScalingConstant();
    float getScalingYConstant();
    void setWalkStanceJumpSideJump(const char*, const char*, const char*, const char*, const char*);

    void setWalk(const char*);
    void setStance(const char*);
    void setJump(const char*);
    void setSideJump(const char*);
    void setDuck(const char*);

    char* getWalk(unsigned char);
    char* getStance(unsigned char);
    char* getJump(unsigned char);
    char* getDuck(unsigned char);
    char* getSideJump(unsigned char);

    struct charactersFile {
		const char* movementName;
		char* fileName;
		int characterNumber;
	};
    std::list<charactersFile*> *getCharacterMovements();

    unsigned char getCantidadPersonajes();
    void setCantidadPersonajes();

private:
    static Util* instance;
    //ventana
    int windowWidth;
    int windowHeight;
    //ventana logica
    float logicalWindowWidth;
    float logicalWindowHeight;
    //escenario
    float logicalStageWidth;
    //personaje
    static unsigned char cantidadPersonajes;
    char* walk[16];
    char* stance[16];
    char* jump[16];
    char* sideJump[16];
    char* duck[16];

	std::list<charactersFile*>* characterMovements;

	void addMovement(const char*, const char*);
};


#endif //MORTALKOMBAT_TALLER1C2015_UTIL_H
