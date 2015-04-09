#include "Layer.h"
#include "../MKCharacter.h"

Layer::Layer(float width) {
    this->width = width;
    //Here depending on the width, the speed is set. Now depends of the z-index
    this->path = "default.png";
    this->speed = this->width / ANCHOVENTANAL;
    this->left_border = 0;

    timeCheck = SDL_GetTicks();
}

Layer::Layer(float width, string path) {
    this->width = width;
    this->path = path;
    //Here depending on the width, the speed is set. Now depends of the z-index
    this->speed = this->width / ANCHOVENTANAL;
    this->left_border = 0;
    timeCheck = SDL_GetTicks();
}

Layer::~Layer() {

}

string Layer::getPath() {
    return this->path;
}

float Layer::getWidth() {
    return this->width;
}

void Layer::setWidth(float width) {
    this->width = width;
}

float Layer::getSpeed() {
    return this->speed;
}

void Layer::setLeft_border(float left_border) {
    this->left_border = left_border;
}

float Layer::getLeft_border() {
    float aux = this->left_border;
    return aux;
}

void Layer::moveLeft() {
    if (this->left_border >= 0)
        this->left_border -= speed;
}

void Layer::moveRight() {
    if (this->left_border + ANCHOVENTANAL < ANCHOESCENARIO)
        this->left_border += speed;
}

void Layer::update() {
    if (timeCheck + 5 < SDL_GetTicks()) {
        if (movement == "RIGHT") {
            this->moveRight();
        }
        else if (movement == "LEFT") {
            this->moveLeft();
        }
        timeCheck = SDL_GetTicks();
    }

}

void Layer::setMovement(string move) {
    movement = move;
}
