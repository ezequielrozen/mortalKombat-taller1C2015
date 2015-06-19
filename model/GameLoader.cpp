#include "GameLoader.h"
#include "CargaJson.h"

GameLoader::GameLoader() {
    this->layers = new list<Layer*>();
    this->characters = new list<MKCharacter*>();
    this->combo1 = new vector<Events>();
    this->combo2 = new vector<Events>();
    this->combo3 = new vector<Events>();
    this->combo4 = new vector<Events>();
    this->combo5 = new vector<Events>();
    this->combo6 = new vector<Events>();
    this->fatality = new vector<Events>();
}

void GameLoader::loadJSON(char* passed_path) {

    extern logger* Mylog;
    char* file = "Escenario.json";
    if(passed_path != NULL){
        file = passed_path;
    }
    double initialH, finalH, offset;
    bool respuesta = cargaArchivoJSON(file, stageWidth, stageHeight, floor, oponentSide, layers, this->characters,
                                      initialH, finalH, offset, this->combo1, this->combo2,this->combo3,this->combo4,
                                      this->combo5,this->combo6,this->fatality);

    if (!respuesta)
    {

    	cargaArchivoJSON("Escenario.json", stageWidth, stageHeight, floor, oponentSide, layers, this->characters,
                         initialH, finalH, offset, this->combo1, this->combo2,this->combo3,this->combo4,this->combo5,
                         this->combo6,this->fatality);

    	Mylog->Log("Cargando Escenario default por JSON mal formado. ", ERROR_LEVEL_WARNING);
    }


    this->stage = new Stage(layers, stageWidth, stageHeight, floor);
    this->painter = new Painter(initialH, finalH, offset);
}

GameLoader::~GameLoader() {
    fatality->clear();
    fatality->shrink_to_fit();
    combo1->clear();
    combo1->shrink_to_fit();
    combo2->clear();
    combo2->shrink_to_fit();
    combo3->clear();
    combo3->shrink_to_fit();
    combo4->clear();
    combo4->shrink_to_fit();
    combo5->clear();
    combo5->shrink_to_fit();
    combo6->clear();
    combo6->shrink_to_fit();

    delete fatality;
    delete combo1;
    delete combo2;
    delete combo3;
    delete combo4;
    delete combo5;
    delete combo6;
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
    return this->combo2;
}

vector<Events>* GameLoader::getCombo3() {
    return this->combo3;
}
vector<Events>* GameLoader::getCombo4() {
    return this->combo4;
}
vector<Events>* GameLoader::getCombo5() {
    return this->combo5;
}
vector<Events>* GameLoader::getCombo6() {
    return this->combo6;
}

vector<Events>* GameLoader::getFatality() {
    return this->fatality;
}
