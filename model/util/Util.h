#ifndef MORTALKOMBAT_TALLER1C2015_UTIL_H
#define MORTALKOMBAT_TALLER1C2015_UTIL_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

class Util {

public:
    static Util* getInstance();
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
    char* getWalk();
    char* getStance();
    char* getJump();
    char* getDuck();
    char* getSideJump();
    void setWalk(const char*, unsigned char);
    void setStance(const char*, unsigned char);
    void setJump(const char*, unsigned char);
    void setSideJump(const char*, unsigned char);
    char* getWalk(unsigned char);
    char* getStance(unsigned char);
    char* getJump(unsigned char);
    char* getDuck(unsigned char);
    char* getSideJump(unsigned char);

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
};


#endif //MORTALKOMBAT_TALLER1C2015_UTIL_H
