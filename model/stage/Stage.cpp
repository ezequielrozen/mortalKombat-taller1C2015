#include "Stage.h"


Stage::Stage(std::list<Layer*>* passed_layers, float passed_width, float passed_heigh, float passed_floor) {
    this->layers = passed_layers;
    this->width = passed_width;
    this->height = passed_heigh;
    this->floor = passed_floor;
}

Stage::~Stage() {

}

std::list<Layer *> *Stage::getLayers() {
    return this->layers;
}

void Stage::setLayers(std::list<Layer *> *passed_layers) {
    this->layers = passed_layers;
}

float Stage::getWidth() {
    return this->width;
}

float Stage::getHeight() {
    return this->height;
}

float Stage::getFloor() {
    return this->floor;
}
