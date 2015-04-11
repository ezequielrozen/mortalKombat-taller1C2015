#include <iostream>
#include "CargaJson.h"

using namespace std;

logger* Mylog;

int main(int argc, char* argv[]) {

    Mylog = new logger("./Mylog.txt", ERROR_LEVEL_ALL);

    Mylog->Log("Iniciando MortalKombat", ERROR_LEVEL_INFO);

    GameLoader* gameLoader = new GameLoader();

    Game* game = new Game(gameLoader, argv[1]);

	game->GameLoop();

	delete game;


    Mylog->Log("Saliendo del programa", ERROR_LEVEL_INFO);
    delete Mylog;

	return 0;
}
