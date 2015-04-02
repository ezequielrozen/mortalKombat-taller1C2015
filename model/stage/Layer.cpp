#include "Layer.h"

Layer::Layer(float width, int z_index) {
    this->width = width;
    this->z_index = z_index;
    //Here depending on the width, the speed is set.
}

Layer::~Layer() {

}

void Layer::move() {

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
