#include "Stage.h"


Stage::Stage(std::list<Layer*>* passed_layers, int passed_width, int passed_heigh, int passed_floor) {
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
