#include "Layer.h"
#include "../MKCharacter.h"

Layer::Layer(float width) {
    this->width = width;
    this->path = "default.png";
    this->left_border = 0;
}

Layer::Layer(float width, string path) {
    this->width = width;
    this->path = path;
    this->speed = ((this->getWidth() - ANCHOVENTANAL) / ANCHOESCENARIO) * VELOCIDAD_DESPLAZAMIENTO_CAPAS;
    if (this->width <= ANCHOVENTANAL)
        this->speed = 0;
    this->left_border = 0;
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
        this->left_border -= speed ;
}

void Layer::moveRight() {
    if (this->left_border + ANCHOVENTANAL < this->getWidth())
        this->left_border += speed;
}

void Layer::update() {
        if (movement == "RIGHT") {
            this->moveRight();
        }
        else if (movement == "LEFT") {
            this->moveLeft();
        }
}

void Layer::setMovement(string move) {
    movement = move;
}
