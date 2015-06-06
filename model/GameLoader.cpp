#include "GameLoader.h"
#include "CargaJson.h"

GameLoader::GameLoader() {
    this->layers = new list<Layer*>();
    this->characters = new list<MKCharacter*>();
    this->combo1 = new vector<Events>();
    this->combo2 = new vector<Events>();
}

void GameLoader::loadJSON(char* passed_path) {

    extern logger* Mylog;
    char* file = "Escenario.json";
    if(passed_path != NULL){
        file = passed_path;
    }
    double initialH, finalH, offset;
    bool respuesta = cargaArchivoJSON(file, stageWidth, stageHeight, floor, oponentSide, layers, this->characters,
                                      initialH, finalH, offset, this->combo1, this->combo2);

    if (!respuesta)
    {

    	cargaArchivoJSON("Escenario.json", stageWidth, stageHeight, floor, oponentSide, layers, this->characters,
                         initialH, finalH, offset, this->combo1, this->combo2);

    	Mylog->Log("Cargando Escenario default por JSON mal formado. ", ERROR_LEVEL_WARNING);
    }


    this->stage = new Stage(layers, stageWidth, stageHeight, floor);
    this->painter = new Painter(initialH, finalH, offset);
}

GameLoader::~GameLoader() {
    delete this->layers;
    delete this->stage;
    std::list<MKCharacter*>::iterator it = this->characters->begin();
    for(it; it != this->characters->end(); it++) {
        delete (*it);
    }
    delete this->characters;
    delete this->painter;
}

string GameLoader::getOponentSide() {
    return this->oponentSide;
}

Stage *GameLoader::getStage() {
    return this->stage;
}

list<MKCharacter *>* GameLoader::getCharacters() {
    return this->characters;
}

Painter *GameLoader::getPainter() {
    return this->painter;
}

vector<Events>* GameLoader::getCombo1() {
    return this->combo1;
}

vector<Events>* GameLoader::getCombo2() {
    return this->combo1;
}
