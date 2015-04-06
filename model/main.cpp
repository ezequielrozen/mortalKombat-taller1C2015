#include <iostream>
#include "Game.h"
#include "CargaJson.h"
#include "logger.h"

using namespace std;

logger* Mylog;

int main(int argc, char* argv[]) {

    Mylog = new logger("./Mylog.txt", ERROR_LEVEL_ALL);

    Mylog->Log("Iniciando MortalKombat", ERROR_LEVEL_INFO);

    int anchoPantalla;
    int altoPantalla;
    float anchoPantallaLogico;
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
    carga = cargaArchivoJSON(file, anchoPantalla, altoPantalla, anchoPantallaLogico, charAncho,
                                    charAlto, stageWidth, stageHeight, floor, oponentSide,
                                    layers, z_index);

    if(!carga){
        char* file = "Escenario.json";
        carga = cargaArchivoJSON(file, anchoPantalla, altoPantalla, anchoPantallaLogico, charAncho,
                                    charAlto, stageWidth, stageHeight, floor, oponentSide,
                                    layers, z_index);
    }
    if(!carga){
        return 1;
    }



    //Load stage
    Stage* stage = new Stage(layers, stageWidth, stageHeight, floor);

    cout << "ancho: " <<anchoPantalla << endl;
    cout << "alto: " <<altoPantalla << endl;

    Game* game = new Game(anchoPantalla, altoPantalla, anchoPantallaLogico, charAncho, charAlto, stage, oponentSide, z_index);

	game->GameLoop();

	delete game;
    delete layers;
    delete stage;


    Mylog->Log("Saliendo del programa", ERROR_LEVEL_INFO);
    delete Mylog;

	return 0;
}
