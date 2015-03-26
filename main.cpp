#include <iostream>
#include "SDL2/SDL.h"
#include "MKMain.h"
#include <zlib.h>
#include <png.h>
#include "SDL2/SDL_image.h"
#include <string>
using namespace std;

int main() {

	MKMain* mkMain = new MKMain(700, 500);

	mkMain->GameLoop();

	delete mkMain;

}
