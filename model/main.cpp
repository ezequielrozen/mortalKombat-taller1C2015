#include <iostream>
#include "Game.h"
#include "CargaJson.h"
#include "logger.h"
#include "util/Util.h"

using namespace std;

logger* Mylog;

int main(int argc, char* argv[]) {

    Mylog = new logger("./Mylog.txt", ERROR_LEVEL_ALL);

    Mylog->Log("Iniciando MortalKombat", ERROR_LEVEL_INFO);

    float stageWidth;
    float stageHeight;
    float charAncho;
    float charAlto;
    float floor;
    int z_index;
    string oponentSide;
    //Load layers
    list<Layer*>* layers = new list<Layer*>();

    char* file = "Escenario.json";
    if(argc > 1){
        file = argv[1];
    }
    bool carga = false;
    carga = cargaArchivoJSON(file, charAncho, charAlto, stageWidth, stageHeight, floor, oponentSide, layers, z_index);

    if(!carga){
        carga = cargaArchivoJSON(file, charAncho, charAlto, stageWidth, stageHeight, floor, oponentSide, layers, z_index);
    }

    //Load stage
    Stage* stage = new Stage(layers, stageWidth, stageHeight, floor);


    Game* game = new Game(Util::getInstance()->getWindowWidth(), Util::getInstance()->getWindowHeight(),
                          Util::getInstance()->getLogicalWindowWidth(), charAncho, charAlto, stage, oponentSide, z_index);

	game->GameLoop();

	delete game;
    delete layers;
    delete stage;


    Mylog->Log("Saliendo del programa", ERROR_LEVEL_INFO);
    delete Mylog;

	return 0;
}
