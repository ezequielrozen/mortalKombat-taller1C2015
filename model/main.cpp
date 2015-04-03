#include <iostream>
#include "Game.h"
#include "CargaJson.h"

using namespace std;

int main(int argc, char* argv[]) {

    int anchoPantalla;
    int altoPantalla;
    float charAncho;
    float charAlto;
    bool carga = cargaArchivoJSON(argv[1], anchoPantalla, altoPantalla, charAncho, charAlto);

	if(!carga){
        return 1;
	}

	Game* game = new Game(anchoPantalla, altoPantalla, charAncho, charAlto);

	game->GameLoop();

	delete game;

	return 0;
}
