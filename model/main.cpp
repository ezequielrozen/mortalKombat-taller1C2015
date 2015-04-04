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
    bool carga = cargaArchivoJSON(argv[1], anchoPantalla, altoPantalla, charAncho, charAlto, stageWidth, stageHeight, floor);

	if(!carga) {
        char* file = "Escenario.json";
        cargaArchivoJSON(file, anchoPantalla, altoPantalla, charAncho, charAlto, stageWidth, stageHeight, floor);
	}

    //Load layers
    list<Layer*>* layers = new list<Layer*>();
    Layer* subwayLayer = new Layer(266);
    layers->push_back(subwayLayer);
    Layer* aLayer = new Layer(617);
    layers->push_back(aLayer);


    //Load stage
    Stage* stage = new Stage(layers, stageWidth, stageHeight, floor);

	Game* game = new Game(anchoPantalla, altoPantalla, charAncho, charAlto, stage);

	game->GameLoop();

	delete game;
    delete aLayer;
    delete subwayLayer;
    delete layers;
    delete stage;

	return 0;
}
