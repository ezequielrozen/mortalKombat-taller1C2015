#include <iostream>
#include "MKMain.h"

using namespace std;

int main() {

	MKMain* mkMain = new MKMain(700, 500);

	mkMain->GameLoop();

	delete mkMain;

	return 0;
}
