#include "Util.h"

using namespace std;

Util* Util::instance = 0;

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

float Util::getLogicalStageWidth() {
    return this->logicalStageWidth;
}

void Util::setLogicalStageWidth(float stageWidth) {
    this->logicalStageWidth = stageWidth;
}

void Util::setWalk(const char* p){//tal vez joda valgrind
    this->walk = strdup(p);
}

void Util::setStance(const char* p){
    this->stance = strdup(p);
}

void Util::setJump(const char* p){
    this->jump = strdup(p);
}

void Util::setSideJump(const char* p){
    this->sideJump = strdup(p);
}

char* Util::getWalk(){return this->walk;}
char* Util::getStance(){return this->stance;}
char* Util::getJump(){return this->jump;}
char* Util::getSideJump(){return this->sideJump;}

