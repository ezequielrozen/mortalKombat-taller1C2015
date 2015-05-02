#include <iostream>
#include "Game.h"

using namespace std;

logger* Mylog;

int main(int argc, char* argv[]) {

    Mylog = new logger("./Mylog.txt", ERROR_LEVEL_ALL); // debug con todo
 //   Mylog = new logger("./Mylog.txt", ERROR_LEVEL_ALL & ~ERROR_LEVEL_INFO); //warning y errores
//    Mylog = new logger("./Mylog.txt", ERROR_LEVEL_ERROR); // errores

    Mylog->Log("Iniciando MortalKombat", ERROR_LEVEL_INFO);

    bool restart = true;

    while (restart) {

        GameLoader* gameLoader = new GameLoader();

        Game* game = new Game(gameLoader, argv[1]);

	    restart = game->GameLoop();

	    delete game;

    };


    Mylog->Log("Saliendo del programa", ERROR_LEVEL_INFO);
    delete Mylog;

	return 0;
}
