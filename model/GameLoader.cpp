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

    bool respuesta = cargaArchivoJSON(file, characterWidth, characterHeight, stageWidth, stageHeight,
                            floor, oponentSide, layers, z_index);

    if (!respuesta)
    {

    	cargaArchivoJSON("Escenario.json", characterWidth, characterHeight, stageWidth, stageHeight,
    	                            floor, oponentSide, layers, z_index);

    	Mylog->Log("Cargando Escenario default por JSON mal formado. ", ERROR_LEVEL_WARNING);
    }


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
