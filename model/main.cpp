#include <iostream>
#include "Game.h"

using namespace std;

int main() {

	Game* game = new Game(700, 500);

	game->GameLoop();

	delete game;

	return 0;
}
