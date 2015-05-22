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

    struct charactersFile {
		const char* movementName;
		char* fileName;
		int characterNumber;
	};
    std::list<charactersFile*> *getCharacterMovements();
    void addMovement(const char*, const char*);

    unsigned char getCantidadPersonajes();
    void setCantidadPersonajes();

    unsigned char getMapaDeCaracteres(int i);
    void setMapaDeCaracteres(unsigned char m, int i);

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

	std::list<charactersFile*>* characterMovements;


    unsigned char mapaDeCaracteres[25];
};


#endif //MORTALKOMBAT_TALLER1C2015_UTIL_H
