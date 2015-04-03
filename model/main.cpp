#include <iostream>
#include "Game.h"
#include "CargaJson.h"

using namespace std;

int main(int argc, char* argv[]) {

	bool carga = cargaArchivoJSON(argv[1]);

	Game* game = new Game(700, 500);

	game->GameLoop();

	delete game;

	return 0;
}
