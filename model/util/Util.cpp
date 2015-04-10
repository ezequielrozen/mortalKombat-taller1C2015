#include "Util.h"

Util* Util::instance = nullptr;

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
