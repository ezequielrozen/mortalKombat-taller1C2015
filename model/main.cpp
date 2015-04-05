#include <iostream>
#include "Game.h"
#include "CargaJson.h"

using namespace std;

int main(int argc, char* argv[]) {

    int anchoPantalla;
    int altoPantalla;
    float stageWidth;
    float stageHeight;
    float charAncho;
    float charAlto;
    float floor;
    string oponentSide;
    //Load layers
    list<Layer*>* layers = new list<Layer*>();

    char* file = argv[1];

    bool carga = cargaArchivoJSON(file, anchoPantalla, altoPantalla, charAncho,
                                    charAlto, stageWidth, stageHeight, floor, oponentSide,
                                    layers);
    if(!carga){
        char* file = "Escenario.json";
        carga = cargaArchivoJSON(file, anchoPantalla, altoPantalla, charAncho,
                                    charAlto, stageWidth, stageHeight, floor, oponentSide,
                                    layers);
    }
    if(!carga){
        return 1;
    }



    //Load stage
    Stage* stage = new Stage(layers, stageWidth, stageHeight, floor);

    cout << "ancho: " <<anchoPantalla << endl;
    cout << "alto: " <<altoPantalla << endl;

    Game* game = new Game(anchoPantalla, altoPantalla, charAncho, charAlto, stage, oponentSide);

	game->GameLoop();

	delete game;
    delete layers;
    delete stage;

	return 0;
}
