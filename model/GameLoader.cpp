#include "GameLoader.h"
#include "CargaJson.h"

GameLoader::GameLoader() {
    this->layers = new list<Layer*>();
}

void GameLoader::loadJSON(char* passed_path) {

    extern logger* Mylog;
    char* file = "Escenario.json";
    if(passed_path != NULL){
        file = passed_path;
    }

    cargaArchivoJSON(file, characterWidth, characterHeight, stageWidth, stageHeight, floor, oponentSide, layers, z_index);

    this->stage = new Stage(layers, stageWidth, stageHeight, floor);
}

GameLoader::~GameLoader() {
    delete this->layers;
    delete this->stage;
}

float GameLoader::getCharacterWidth() {
    return this->characterWidth;
}

float GameLoader::getCharacterHeight() {
    return characterHeight;
}

int GameLoader::getZ_index() {
    return this->z_index;
}


string GameLoader::getOponentSide() {
    return this->oponentSide;
}

Stage *GameLoader::getStage() {
    return this->stage;
}
