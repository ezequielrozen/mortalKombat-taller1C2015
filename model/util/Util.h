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
    void setWalk(const char*);
    void setStance(const char*);
    void setJump(const char*);
    void setSideJump(const char*);
    char* getWalk();
    char* getStance();
    char* getJump();
    char* getSideJump();

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
    char* walk;
    char* stance;
    char* jump;
    char* sideJump;
};


#endif //MORTALKOMBAT_TALLER1C2015_UTIL_H
