#include "Layer.h"

Layer::Layer(int width, int z_index) {
    this->width = width;
    this->z_index = z_index;
    //Here depending on the width, the speed is set. Now depends of the z-index
    this->speed = this->z_index*10;
    this->left_border = 0;

    timeCheck = SDL_GetTicks();
}

Layer::~Layer() {

}

int Layer::getWidth() {
    return this->width;
}

void Layer::setWidth(int width) {
    this->width = width;
}

float Layer::getSpeed() {
    return this->speed;
}

void Layer::setLeft_border(int left_border) {
    this->left_border = left_border;
}

int Layer::getLeft_border() {

    int aux = this->left_border;
    this->left_border = 0;

    return aux;
}

void Layer::moveLeft() {
    this->left_border++;
}

void Layer::moveRight() {
    this->left_border--;
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
