#include "Util.h"

using namespace std;

Util* Util::instance = 0;
unsigned char Util::cantidadPersonajes = 0;

Util* Util::getInstance() {

    if (!instance) {
        instance = new Util();
    }
    return instance;
}

int Util::getWindowWidth() {
    return this->windowWidth;
}

int Util::getWindowHeight() {
    return this->windowHeight;
}

float Util::getLogicalWindowWidth() {
    return this->logicalWindowWidth;
}

float Util::getLogicalWindowHeight() {
    return this->logicalWindowHeight;
}

void Util::setWindowWidth(int width) {
    this->windowWidth = width;
}

void Util::setWindowHeight(int height) {
    this->windowHeight = height;
}

void Util::setLogicalWindowWidth(float logicalWidth) {
    this->logicalWindowWidth = logicalWidth;
}

void Util::setLogicalWindowHeight(float logicalHeight) {
    this->logicalWindowHeight = logicalHeight;
}

float Util::getScalingConstant() {
    return this->windowWidth/this->logicalWindowWidth;
}

float Util::getScalingYConstant() {
    return this->windowHeight/this->logicalWindowHeight;
}

float Util::getLogicalStageWidth() {
    return this->logicalStageWidth;
}

void Util::setLogicalStageWidth(float stageWidth) {
    this->logicalStageWidth = stageWidth;
}

void Util::setWalkStanceJumpSideJump(const char* w, const char* s, const char* j, const char* sj, const char* duck){
    this->walk[cantidadPersonajes] = strdup(w);
    this->stance[cantidadPersonajes] = strdup(s);
    this->jump[cantidadPersonajes] = strdup(j);
    this->sideJump[cantidadPersonajes] = strdup(sj);
    this->duck[cantidadPersonajes] = strdup(duck);
    ++cantidadPersonajes;
}

void Util::setWalk(const char* p, unsigned char idPersonaje){
    this->walk[idPersonaje] = strdup(p);
}


void Util::setStance(const char* p, unsigned char idPersonaje){
    this->stance[idPersonaje] = strdup(p);
}


void Util::setJump(const char* p, unsigned char idPersonaje){
    this->jump[idPersonaje] = strdup(p);
}

void Util::setSideJump(const char* p, unsigned char idPersonaje){
    this->sideJump[idPersonaje] = strdup(p);
}

char* Util::getWalk(){return this->walk[0];}
char* Util::getStance(){return this->stance[0];}
char* Util::getJump(){return this->jump[0];}
char* Util::getSideJump(){return this->sideJump[0];}
char* Util::getDuck(){return this->duck[0];}

char* Util::getWalk(unsigned char id){return this->walk[id];}
char* Util::getStance(unsigned char id){return this->stance[id];}
char* Util::getJump(unsigned char id){return this->jump[id];}
char* Util::getSideJump(unsigned char id){return this->sideJump[id];}
char* Util::getDuck(unsigned char id){return this->duck[id];}


